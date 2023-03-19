#include <string>
#include <iostream>
#include <memory> // 智能指针, allocator
#include <list>
#include <iomanip>
#include <vector>
#include <new> // bad_alloc, nothrow
#include <stdexcept>
#include <cassert>
#include <sstream>
#include "utils.h"
#include "str_blob.h"
#include "str_blob_ptr.h"
#include "text_query.h"
#include "query_result.h"

class Car
{

public:
  Car(std::string n, std::string c, double p) : name(n), color(c), price(p) {}
  std::string name;
  std::string color;
  double price;
  static std::shared_ptr<Car> new_instance(std::string n, std::string c, double p);
};
std::shared_ptr<Car> Car::new_instance(std::string n, std::string c, double p)
{
  return std::make_shared<Car>(n, c, p);
}

std::ostream &operator<<(std::ostream &os, const Car &c)
{

  os << "Car(" << OUTPUT_MEMBER(c, name) << ", " OUTPUT_MEMBER(c, color) << ", " << OUTPUT_MEMBER(c, price) << ")";
  return os;
}

void demo_shared_ptr()
{

  std::shared_ptr<std::string> p1;
  if (!p1)
  {
    std::cout << OUTPUT_VAL(p1) << " is empty" << std::endl;
  }

  std::shared_ptr<std::list<int>> p2;
  if (!p2)
  {
    std::cout << OUTPUT_VAL(p2) << " is empty" << std::endl;
  }

  auto p3 = std::make_shared<int>(42);
  std::cout << OUTPUT_VAL(*p3) << std::endl;

  auto p4 = std::make_shared<std::string>(10, '9');
  auto p5 = std::make_shared<int>();
  auto p6 = std::make_shared<std::vector<std::string>>();

  p6->push_back("hello");
  p6->push_back("world");
  p6->push_back("yeefea");
  describe_vector(*p6);

  std::cout << OUTPUT_VAL(p6.use_count()) << std::endl;
  auto p7 = p6;
  auto p8 = p6;
  std::cout << OUTPUT_VAL(p6.use_count()) << std::endl;
  std::cout << OUTPUT_VAL(p7.use_count()) << std::endl;
  std::cout << OUTPUT_VAL(p8.use_count()) << std::endl;

  auto car1 = Car::new_instance("Audi", "Gray", 2.39909e5);
  std::cout << *car1 << std::endl;
  std::cout << OUTPUT_VAL(car1.use_count()) << std::endl;
  auto car2 = car1;
  std::cout << OUTPUT_VAL(car1.use_count()) << std::endl;
  std::cout << OUTPUT_VAL(car2.use_count()) << std::endl;
}

void demo_blob()
{

  StrBlob strs;

  strs.push_back("123123");
  strs.push_back("456");
  strs.push_back("789");

  std::cout << OUTPUT_VAL(strs.size()) << std::endl;
}
void demo_new()
{
  auto ps = new std::string("123123123");
  // 用完了再delete

  int *pi = new int; // 默认初始化，内置类型的值是未定义的，而类类型对象的值会用默认构造函数初始化
  std::cout << OUTPUT_VAL(*pi) << std::endl;
  delete pi;
  pi = nullptr; // avoid dangling pointer

  int *pi1 = new int(1024);
  std::cout << OUTPUT_VAL(*pi1) << std::endl;
  delete pi1;
  pi1 = nullptr;

  std::string *ps1 = new std::string;
  std::cout << OUTPUT_VAL(*ps1) << std::endl;
  delete ps1;
  ps1 = nullptr;

  std::string *ps2 = new std::string(10, '9'); // 直接初始化
  std::cout << OUTPUT_VAL(*ps2) << std::endl;
  delete ps2;
  ps2 = nullptr;

  std::vector<int> *pv = new std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // 列表初始化
  // std::cout << OUTPUT_VAL(*pv) << std::endl;
  describe_vector(*pv);
  delete pv;
  pv = nullptr;

  // 值初始化
  int *pi2 = new int(); // 值初始化为0
  std::cout << OUTPUT_VAL(*pi2) << std::endl;
  delete pi2;
  pi2 = nullptr;

  auto p1 = new auto(*ps);
  std::cout << OUTPUT_VAL(*p1) << std::endl;
  delete p1;
  p1 = nullptr;
  delete ps;
  ps = nullptr; // avoid dangling pointer

  // const对象
  const int *pci = new const int(1024);
  std::cout << OUTPUT_VAL(*pci) << std::endl;

  const std::string *pcs = new const std::string(10, '1');
  std::cout << OUTPUT_VAL(*pcs) << std::endl;

  delete pci;
  delete pcs;
}

void demo_oom()
{

  int *p1 = new int;

  // placement new，定位new
  int *p2 = new (std::nothrow) int; // nothrow对象，如果malloc失败，返回空指针而不抛出异常

  std::cout << OUTPUT_VAL(*p1) << ", " << OUTPUT_VAL(*p2) << std::endl;
  delete p1;
  delete p2;
}

void demo_shared_ptr_and_new()
{

  std::shared_ptr<double> p1(new double); // undefined inital value
  std::shared_ptr<int> p2(new int(42));   // 把一个原生指针给智能指针来管

  std::cout << OUTPUT_VAL(*p1) << std::endl;
  std::cout << OUTPUT_VAL(*p2) << std::endl;
}
void release_int(int *pi)
{
  std::cout << OUTPUT_VAL(*pi) << " is deleted." << std::endl;
  delete pi;
}

void smart_ptr_and_exception()
{
  std::shared_ptr<int> sp(new int(42), release_int);
  throw std::range_error("demo smart pointer with exception");
}

void demo_smart_ptr_and_expception()
{

  try
  {
    smart_ptr_and_exception();
  }
  catch (std::range_error err)
  {
    std::cout << OUTPUT_VAL(err.what()) << std::endl;
  }
}

void demo_deleter()
{
  std::shared_ptr<int> pi = std::shared_ptr<int>(new int(42), release_int);
  std::cout << OUTPUT_VAL(*pi) << std::endl;
}

std::unique_ptr<int, decltype(release_int) *> clone_int(int p)
{
  // 创建一个unique_ptr然后返回
  // unique_ptr的delete类型需要写在类型参数里，和shared_ptr不同
  std::unique_ptr<int, decltype(release_int) *> ret(new int(p), release_int);
  return ret;
}

void demo_unique_ptr()
{
  // unique_ptr 只能直接初始化，不能赋值、拷贝，不share对象
  // 但是可以拷贝或赋值一个将要被销毁的unique_ptr，例如函数的返回值可以是unique_ptr
  std::unique_ptr<std::string> p1(new std::string("some ssssss"));
  std::unique_ptr<std::string> p2(p1.release()); // p1放弃控制权并返回原生指针
  std::unique_ptr<std::string> p3;
  p3.reset(p2.release());

  auto pi = clone_int(123);

  std::cout << OUTPUT_VAL(*pi) << std::endl;
}

void demo_weak_ptr()
{
  auto p = std::make_shared<int>(42);
  std::weak_ptr<int> wp(p); // 用shared_ptr初始化weak_ptr，指向shared_ptr管理的对象

  auto np = wp.lock(); // lock返回shared_ptr，要检查对象是否存在
  if (np)
  {
    std::cout << "weak pointer: " << OUTPUT_VAL(*np) << std::endl;
  }

  wp.reset();
}

void demo_str_blob_ptr()
{
  StrBlob blob;
  blob.push_back("one");
  blob.push_back("two");
  blob.push_back("three");
  blob.push_back("four");
  StrBlobPtr sp(blob);
  sp.incr();
  sp.incr();
  auto res = sp.deref();
  assert(res == "three"); // res should be three
  std::cout << OUTPUT_VAL(res) << std::endl;
}

void release_int_array(int *p)
{
  std::cout << "p is deleted." << std::endl;
  delete[] p;
}

void demo_dynamic_array()
{
  constexpr int sz = 42;
  int n = 42;
  int *pia = new int[n];
  describe_array(pia, pia + n);
  delete[] pia;
  pia = nullptr;

  // or
  using arrT = std::string[sz]; // 虽然合法，但是这样定义类型很容易造成delete写错，因为需要delete []
  std::string *p = new arrT;
  describe_array<std::string>(p, p + sz);
  delete[] p;
  p = nullptr;

  // unique_ptr and dynamic array
  std::unique_ptr<int[], decltype(release_int_array) *> up(new int[n], release_int_array); // 类似于Go的slice
  for (int i = 0; i < n; ++i)
  {
    up[i] = i * 2;
  }
  describe_array<int>(up.get(), up.get() + n);

  // shared_ptr and dynamic array
  // shared_ptr不直接支持动态数组管理，需要传入自定义的deleter
  std::shared_ptr<int> sp(
      new int[10], [](int *pia)
      { 
        describe_array(pia, pia+10);
        std::cout  << "delete pia array" << std::endl;
        delete[] pia; });
  sp.reset(); // 释放内存
  assert(sp == nullptr);
}

void demo_allocator()
{
  int n_str = 10;
  std::allocator<std::string> alloc;
  auto const p = alloc.allocate(n_str); // 会根据给定的对象类型来确定恰当的内存大小和对齐位置
  // 此时p指向的内存未初始化！
  auto q = p;
  alloc.construct(q++); // 构造p[0]  deprecated！
  std::cout << OUTPUT_VAL(*p) << std::endl;
  alloc.construct(q++, 10, 'c'); // 构造p[1]
  std::cout << OUTPUT_VAL(*(p + 1)) << std::endl;
  alloc.construct(q++, "hi"); // 构造p[2]
  std::cout << OUTPUT_VAL(*(p + 2)) << std::endl;

  while (q != p)
  {
    alloc.destroy(--q); // 析构上面创建的3个string
  }

  alloc.deallocate(p, n_str); // 释放内存

  std::allocator<int> ialloc;
  std::vector<int> vi = {1, 3, 5, 7, 9, 11, 13};
  auto pi = ialloc.allocate(vi.size() * 2);
  auto qi = std::uninitialized_copy(vi.begin(), vi.end(), pi);
  auto end = std::uninitialized_fill_n(qi, vi.size(), 42);

  describe_array(pi, pi + vi.size() * 2);
  for (auto qq = pi; qq != end; ++qq)
  {
    ialloc.destroy(qq);
  }
  ialloc.deallocate(pi, vi.size() * 2); // 释放内存
}

void demo_text_query()
{

  std::stringstream ss("one two three\nfour five six seven one three\neight nine two\n ten eleven\n");
  TextQuery tq(ss);
  auto res1 = tq.query("one");
  print_query_result(std::cout, res1);

  auto res2 = tq.query("two");
  print_query_result(std::cout, res2);
}

int main(int argc, char **argv)
{
  RUN_DEMO(demo_shared_ptr);
  RUN_DEMO(demo_new);
  RUN_DEMO(demo_oom);
  RUN_DEMO(demo_blob);
  RUN_DEMO(demo_shared_ptr_and_new);
  RUN_DEMO(demo_smart_ptr_and_expception);
  RUN_DEMO(demo_deleter);
  RUN_DEMO(demo_unique_ptr);
  RUN_DEMO(demo_weak_ptr);
  RUN_DEMO(demo_str_blob_ptr);
  RUN_DEMO(demo_dynamic_array);
  RUN_DEMO(demo_allocator);
  RUN_DEMO(demo_text_query);
  return 0;
}