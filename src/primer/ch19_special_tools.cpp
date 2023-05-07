
#include "ch19_special_tools.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
#include <functional>
#include <utility>
#include "utils.h"

void demo_operator()
{
  std::string *sp = new std::string("123123");
  std::cout << OUTPUT_VAL(*sp) << std::endl;
  delete sp;

  std::string *sap = new std::string[5];
  describe_array(sap, sap + 5);
  delete[] sap;

  // placement new
  unsigned char buf[sizeof(int) * 2];

  // placement new in buf
  int *pInt = new (buf) int(3);
  int *qInt = new (buf + sizeof(int)) int(5);
  int *pBuf = (int *)(buf + 0);
  int *qBuf = (int *)(buf + sizeof(int));
  std::cout << "Buff Addr             Int Addr" << std::endl;
  std::cout << pBuf << "             " << pInt << std::endl;
  std::cout << qBuf << "             " << qInt << std::endl;
  std::cout << "------------------------------" << std::endl;
  std::cout << "1st Int             2nd Int" << std::endl;
  std::cout << *pBuf << "                         " << *qBuf << std::endl;
}

void demo_rtti()
{
  // dynamic_cast
  // dynamic_cast<type*>(e), dynamic_cast<type&>(e), dynamic_cast<type&&>(e)

  // 指针类型dynamic_cast，失败返回0
  Base b;
  Derived d;

  Base *bp = &b;

  // Base至少含有一个虚函数，是多态类型，才能dynamic_cast
  // 下转型失败，返回0
  if (Derived *dp = dynamic_cast<Derived *>(bp))
  {
    dp->print(std::cout);
  }
  else
  {
    bp->print(std::cout);
  }
  // 下转型成功
  bp = &d;
  if (Derived *dp = dynamic_cast<Derived *>(bp))
  {
    dp->print(std::cout);
  }
  else
  {
    bp->print(std::cout);
  }

  // 引用类型dynamic_cast
  try
  {
    Derived &dr = dynamic_cast<Derived &>(b);
    std::cout << "downcasting succeed" << std::endl;
  }
  catch (std::bad_cast)
  {
    std::cout << "downcasting failed" << std::endl;
  }

  // typeid，检查bp指向的对象是否是Derived类型
  // 只有定义了虚函数的左值，才会在运行时求值，例如下面的*bp
  // 通常都是 左* == 右class name 这样写
  if (typeid(*bp) == typeid(Derived))
  {
    std::cout << "type if bp is Derived*" << std::endl;
  }
  else
  {
    std::cout << OUTPUT_VAL(typeid(bp).name()) << std::endl;
    std::cout << OUTPUT_VAL(typeid(Derived).name()) << std::endl;
    std::cout << OUTPUT_VAL(typeid(Derived *).name()) << std::endl;
    std::cout << "type if bp is not Derived*" << std::endl;
  }

  // type_info类
  std::cout << OUTPUT_VAL(typeid(42).name()) << std::endl;
  std::string s = "123";
  std::cout << OUTPUT_VAL(typeid(s).name()) << std::endl;
}

void ff(color c) { std::cout << "ff c" << std::endl; }
void ff(int i) { std::cout << "ff i" << std::endl; }

void demo_enum()
{
  color eyes = green;      // unscoped
  color hair = color::red; // unscoped, ok

  peppers p = peppers::yellow; // scoped
  // peppers p = green;  // 不行

  // 类型转换
  int i = color::red; // unscopped, implicit type conversion
  // scopped, only explicit type conversion
  int j = static_cast<int>(peppers::green);

  std::cout << OUTPUT_VAL(eyes) << std::endl;
  std::cout << OUTPUT_VAL(hair) << std::endl;
  std::cout << OUTPUT_VAL(static_cast<int>(p)) << std::endl;
  std::cout << OUTPUT_VAL(i) << std::endl;
  std::cout << OUTPUT_VAL(j) << std::endl;

  ff(eyes);
  ff(green);
  ff(123);
}

// 这个语法比较难，但是挺有用的
void demo_member_pointer()
{
  // 成员变量指针
  // pdata可以指向Screen的string的成员，这语法很迷
  // 普通指针语法      <指向的变量类型>         *<指针变量名>
  // 成员变量指针语法   <指向的变量类型> <类名>::*<指针变量名>，在普通的指针名前面加上类名::
  const std::string Screen::*pdata;

  // 这里pdata指针并没有指向实际的对象，只是记录了一个对象内部的偏移量
  pdata = &Screen::contents;
  // 指向另一个string成员
  pdata = &Screen::contents2;

  auto pdata2 = &Screen::contents2; // 这样更简单
  pdata2 = &Screen::contents;

  Screen myScreen("123123123"), *pScreen = &myScreen;

  // 使用成员指针 点星.* 箭头星->*运算符 4级优先级，左结合，在低于前缀++--，高于*/%数值运算
  // 1 .*
  auto s = myScreen.*pdata;
  std::cout << OUTPUT_VAL(s) << std::endl;

  // 2 ->*
  s = pScreen->*pdata;
  std::cout << OUTPUT_VAL(s) << std::endl;

  // 3 返回成员指针的类函数
  pdata = Screen::data();
  s = myScreen.*pdata;
  std::cout << OUTPUT_VAL(s) << std::endl;

  // 成员函数指针
  auto pmf = &Screen::get_cursor;

  // 因为get函数重载了，必须这样声明函数指针
  // 在普通函数指针前添加类名::
  char (Screen::*pmf2)(Screen::pos, Screen::pos) const;
  pmf2 = &Screen::get;
  // pmf2 = Screen::get; 错误，不能自动将成员函数转换成函数指针

  // 使用成员函数指针，因为函数调用优先级2级很高，高于.*和->*，这里必须加上括号
  char c1 = (pScreen->*pmf)();
  char c2 = (myScreen.*pmf2)(0, 0);

  // 类型别名，增加可读性
  using Action = char (Screen::*)(Screen::pos, Screen::pos) const;
  Action get = &Screen::get;

  // member function -> callable
  std::vector<std::string> svec = {"a", "", "b"};

  // 1
  std::function<bool(const std::string &)> fcn = &std::string::empty;
  auto it = std::find_if(svec.begin(), svec.end(), fcn);
  if (it == svec.end())
  {
    std::cout << "empty string not found" << std::endl;
  }
  else
  {
    std::cout << "found empty string" << std::endl;
  }

  // 2
  it = std::find_if(svec.begin(), svec.end(), std::mem_fn(&std::string::empty));
  if (it == svec.end())
  {
    std::cout << "empty string not found" << std::endl;
  }
  else
  {
    std::cout << "found empty string" << std::endl;
  }

  // 3
  auto f = std::bind(&std::string::empty, std::placeholders::_1);
  f(*svec.begin());
  f(&svec[0]);

  std::string str = "123123";

  std::function<const char *(const std::string &)> ss_func = &std::string::c_str;
  auto c_str = std::bind(ss_func, std::ref(str));

  LOG(c_str());
  // std::bind(ss_func, &ss);
}

void demo_embedded_class()
{
  Outer o;
  Outer::Inner i;
}

void demo_union()
{
  Token first_token = {'a'};
  std::cout << OUTPUT_VAL(first_token.cval) << std::endl;
  std::cout << OUTPUT_VAL(first_token.ival) << std::endl;
  std::cout << OUTPUT_VAL(first_token.dval) << std::endl;

  first_token.ival = 42;
  std::cout << OUTPUT_VAL(first_token.cval) << std::endl;
  std::cout << OUTPUT_VAL(first_token.ival) << std::endl;
  std::cout << OUTPUT_VAL(first_token.dval) << std::endl;
  Token last_token;
  Token *pt = new Token;

  delete pt;

  ComplexToken u;
  std::cout << OUTPUT_VAL(u.ival) << std::endl;

  u.sval = "123123";
  std::cout << OUTPUT_VAL(u.sval) << std::endl;
  std::cout << OUTPUT_VAL(u.ival) << std::endl;
  std::cout << OUTPUT_VAL(u.dval) << std::endl;
}

void demo_local_class() {}

void demo_bit_field()
{
  File f;

  std::cout << OUTPUT_VAL(f.prot_owner) << std::endl;
  std::cout << OUTPUT_VAL(f.prot_group) << std::endl;
  std::cout << OUTPUT_VAL(f.prot_world) << std::endl;

  f.open(File::WRITE);
  f.write();
  f.close();
}

void demo_volatile()
{
  // 语法和const类似，有顶层volatile和底层volatile
  volatile int display_register;
  volatile int *ivp = &display_register; // 底层
  int i = 9;
  int *volatile vip = &i; // 顶层

  volatile int iax[100];

  describe_array(iax, iax + 100);
}

#ifdef __cplusplus

extern "C" int strcmp(const char *, const char *);

void demo_extern_c()
{
  auto res = strcmp("123", "456");
  std::cout << OUTPUT_VAL(res) << std::endl;
}
#endif

int main(int argc, char **argv)
{
  RUN_DEMO(demo_operator);
  RUN_DEMO(demo_rtti);
  RUN_DEMO(demo_enum);
  RUN_DEMO(demo_member_pointer);
  RUN_DEMO(demo_embedded_class);
  RUN_DEMO(demo_union);
  RUN_DEMO(demo_local_class);
  RUN_DEMO(demo_bit_field);
  RUN_DEMO(demo_volatile);
#ifdef __cplusplus
  RUN_DEMO(demo_extern_c);
#endif
  return EXIT_SUCCESS;
}