#include <algorithm>
#include <iostream>
#include <string>
#include <utility>  // move

#include "has_ptr.h"
#include "nocopy.h"
#include "nodtor.h"
#include "utils.h"

/*
拷贝控制
资源管理
*/

class DemoObject {
 public:
  DemoObject();
  DemoObject(const DemoObject &) = default;
  DemoObject &operator=(const DemoObject &rhs) = default;
  ~DemoObject() = default;

  int m1;
  double m2;
  std::string sarr[10];  // 合成拷贝会复制数组，很方便
};

DemoObject::DemoObject() : m1(1), m2(2.0) {}

std::ostream &operator<<(std::ostream &os, const DemoObject &obj) {
  os << "DemoObject(" << OUTPUT_MEMBER(obj, m1) << ", " OUTPUT_MEMBER(obj, m2)
     << ", sarr=";
  serialize_arr(os, obj.sarr, obj.sarr + 10);
  os << ")";

  return os;
}

class Sales_data {
 public:
  Sales_data(const Sales_data &);  // copy constructor
 private:
  std::string bookNo;
  int units_sold = 0;
  double revenue = 0.0;
};

Sales_data::Sales_data(const Sales_data &orig)
    : bookNo(orig.bookNo), units_sold(orig.units_sold), revenue(orig.revenue) {}

class Foo {
 public:
  Foo() { std::cout << "Foo default constructor called" << std::endl; };
  Foo(const Foo
          &)  // 拷贝构造函数，第一个参数是类型自身的引用，其他任何参数都有默认值。几乎总是const引用。通常不加explicit。
  {
    std::cout << "Foo copy constructor called" << std::endl;
  };
  ~Foo() { std::cout << "Foo destructor called" << std::endl; }
  Foo &operator=(const Foo &);

 private:
  int val;
};

void demo_copy_construct_desctruct() {
  Foo f;       // default constructor
  Foo f1(f);   // copy constructor
  Foo f2 = f;  // copy constructor

  // destructor

  std::string dots(10, '.');  // 直接
  std::string s(dots);        // 直接初始化
  std::string s2 = dots;
  std::string null_book = "999999-99999";
  std::string nines = std::string(100, '9');

  DemoObject obj;

  obj.sarr[3] = "123123123";
  std::cout << obj << std::endl;

  DemoObject obj2;

  obj2 = obj;
  std::cout << obj2 << std::endl;
}

void demo_rule_3_5() {
  // 阻止拷贝
  NoCopy nc;
  // NoCopy nc2(nc); error
  NoCopy nc2;
  // nc2 = nc; error

  NoDtor *p = new NoDtor();

  // delete p; error
}
void demo_copy_control() {
  HasPtrLikePtr ptr1("ppp");
  std::cout << OUTPUT_VAL(ptr1.refcnt()) << std::endl;

  HasPtrLikePtr ptr2 = ptr1;
  std::cout << OUTPUT_VAL(ptr1.refcnt()) << std::endl;
  std::cout << OUTPUT_VAL(ptr2.refcnt()) << std::endl;

  HasPtrLikePtr ptr3(ptr1);
  std::cout << OUTPUT_VAL(ptr1.refcnt()) << std::endl;
  std::cout << OUTPUT_VAL(ptr2.refcnt()) << std::endl;
  std::cout << OUTPUT_VAL(ptr3.refcnt()) << std::endl;
}

void demo_swap() {
  HasPtrLikeValue val1("123123123");
  HasPtrLikeValue val2;

  val2 = val1;
}

struct DefaultMove {
  // iff
  // 一个类没有定义任何拷贝控制成员，且每个非static数据成员都可以移动，则编译器会合成移动构造函数和移动赋值运算符
  int i;          // 内置类型可以move
  std::string s;  // string定义了move操作
};

struct CanMove {
  DefaultMove mem;  // 有合成的移动操作
};

class SortableObj {
 public:
  SortableObj sorted() &&;
  SortableObj sorted() const
      &;  // 同名同参数的函数，如果其中一个有引用限限定符，则所有都必须有引用限定符
          // SortableObj sorted() const ; //
  // 这样是错的，重载参数类型相同的两个成员函数需要它们同时具有或缺少引用限定符C/C++(2449)

 private:
  std::vector<int> data;
};

SortableObj SortableObj::sorted() && {
  std::sort(data.begin(), data.end());
  return *this;
}

SortableObj SortableObj::sorted() const & {
  SortableObj ret(*this);
  std::sort(ret.data.begin(), ret.data.end());
  return ret;
}

void process_r_ref(std::string &&s) {
  //
  std::cout << OUTPUT_VAL(s) << std::endl;
}

void demo_move() {
  /*
  lvalue
  xvalue
  prvalue

  glvalue
    lvalue
    xvalue

  rvalue
    prvalue
    xvalue
  */

  int i = 42;
  // rvalue ref
  // 右值引用能指向右值，本质上也是把右值提升为一个左值，并定义一个右值引用通过std::move指向该左值
  // 被声明出来的左、右值引用都是左值。
  // 因为被声明出的左右值引用是有地址的，也位于等号左边。
  // 右值引用既可以是左值也可以是右值，如果有名称则为左值，否则是右值。
  // 或者说：作为函数返回值的 && 是右值，直接声明出来的 && 是左值。
  int &&rr = i * 42;
  std::cout << OUTPUT_VAL(rr) << std::endl;

  ++rr;
  std::cout << OUTPUT_VAL(rr) << std::endl;
  std::move(i);

  const int &r3 = i * 42;  // const引用可以绑定到右值上

  int &&rr1 = 42;
  int &&rr3 = std::move(rr1);

  Foo x;
  Foo y(x);
  Foo z(std::move(
      x));  // 因为Foo没有移动构造函数，所以即使用了move还是调用拷贝构造函数，Foo&&转const
            // Foo&

  std::string s = "123";
  std::string &ref_s = s;
  std::string &&r_ref_s = std::move(s);
  std::string &&r_ref_s2 = std::move(r_ref_s);
  std::cout << OUTPUT_VAL(s) << std::endl;
  std::cout << OUTPUT_VAL(ref_s) << std::endl;
  std::cout << OUTPUT_VAL(r_ref_s) << std::endl;
  std::cout << OUTPUT_VAL(r_ref_s2) << std::endl;

  std::string s2(r_ref_s2);  // 依然是拷贝构造，因为r_ref_s2本身是左值
  std::cout << OUTPUT_VAL(s) << std::endl;
  std::cout << OUTPUT_VAL(ref_s) << std::endl;
  std::cout << OUTPUT_VAL(r_ref_s) << std::endl;
  std::cout << OUTPUT_VAL(r_ref_s2) << std::endl;
  std::cout << OUTPUT_VAL(s2) << std::endl;

  std::string s3(std::move(r_ref_s2));
  std::cout << OUTPUT_VAL(s) << std::endl;
  std::cout << OUTPUT_VAL(ref_s) << std::endl;
  std::cout << OUTPUT_VAL(r_ref_s) << std::endl;
  std::cout << OUTPUT_VAL(r_ref_s2) << std::endl;
  std::cout << OUTPUT_VAL(s3) << std::endl;
  std::cout << OUTPUT_VAL(s2) << std::endl;

  std::vector<std::string> vs;
  vs.push_back(std::move(s3));
  // 现在s3为空了，移到了vs里
  describe_vector(vs);
  std::cout << OUTPUT_VAL(s3) << std::endl;
}

int main(int argc, char **argv) {
  RUN_DEMO(demo_copy_construct_desctruct);
  RUN_DEMO(demo_rule_3_5);
  RUN_DEMO(demo_copy_control);
  RUN_DEMO(demo_swap);
  RUN_DEMO(demo_move);
}