#include <string>
#include <iostream>
#include "utils.h"
#include "nocopy.h"
#include "nodtor.h"
#include "has_ptr.h"

class DemoObject
{
public:
  DemoObject();
  DemoObject(const DemoObject &) = default;
  DemoObject &operator=(const DemoObject &rhs) = default;
  ~DemoObject() = default;

  int m1;
  double m2;
  std::string sarr[10]; // 合成拷贝会复制数组，很方便
};

DemoObject::DemoObject() : m1(1), m2(2.0) {}

std::ostream &operator<<(std::ostream &os, const DemoObject &obj)
{

  os << "DemoObject(" << OUTPUT_MEMBER(obj, m1) << ", " OUTPUT_MEMBER(obj, m2) << ", sarr=";
  serialize_arr(os, obj.sarr, obj.sarr + 10);
  os << ")";

  return os;
}

class Sales_data
{
public:
  Sales_data(const Sales_data &); // copy constructor
private:
  std::string bookNo;
  int units_sold = 0;
  double revenue = 0.0;
};

Sales_data::Sales_data(const Sales_data &orig) : bookNo(orig.bookNo),
                                                 units_sold(orig.units_sold),
                                                 revenue(orig.revenue)
{
}

class Foo
{
public:
  Foo()
  {
    std::cout << "Foo default constructor called" << std::endl;
  };
  Foo(const Foo &) // 拷贝构造函数，第一个参数是类型自身的引用，其他任何参数都有默认值。几乎总是const引用。通常不加explicit。
  {
    std::cout << "Foo copy constructor called" << std::endl;
  };
  ~Foo()
  {
    std::cout << "Foo destructor called" << std::endl;
  }
  Foo &operator=(const Foo &);

private:
  int val;
};

void demo_copy_construct_desctruct()
{
  Foo f;      // default constructor
  Foo f1(f);  // copy constructor
  Foo f2 = f; // copy constructor

  // destructor

  std::string dots(10, '.'); // 直接
  std::string s(dots);       // 直接初始化
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

void demo_rule_3_5()
{
  // 阻止拷贝
  NoCopy nc;
  // NoCopy nc2(nc); error
  NoCopy nc2;
  // nc2 = nc; error

  NoDtor *p = new NoDtor();

  // delete p; error
}
void demo_copy_control()
{
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

void demo_swap()
{
  
}
void demo_move()
{

  int i = 42;
  // rvalue
  int &&rr = i * 42;
  const int &r3 = i * 42;
}

int main(int argc, char **argv)
{
  RUN_DEMO(demo_copy_construct_desctruct);
  RUN_DEMO(demo_rule_3_5);
  RUN_DEMO(demo_copy_control);
  RUN_DEMO(demo_swap);
  RUN_DEMO(demo_move);
}