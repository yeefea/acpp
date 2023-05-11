#include <iostream>
#include <cstdlib>
#include <cstring>
#include "utils.h"
#define DESC_TYPE(T) std::cout << "size of " #T " is " << sizeof(T) << " bytes." << std::endl

// const只能在文件内使用，如果要跨文件，需要extern const
extern const int bufsize;

struct RegularStruct
{
  unsigned char Field1;
  unsigned int Field2;
};

struct PackedStruct
{
  unsigned char Field1;
  unsigned int Field2;
} __attribute__((packed));

void demo_types()
{
  DESC_TYPE(bool);

  DESC_TYPE(char);
  DESC_TYPE(signed char);
  DESC_TYPE(unsigned char);

  DESC_TYPE(wchar_t);
  DESC_TYPE(char16_t);
  DESC_TYPE(char32_t);

  DESC_TYPE(short);
  DESC_TYPE(int);
  DESC_TYPE(long);
  DESC_TYPE(long long);
  DESC_TYPE(unsigned short);
  DESC_TYPE(unsigned int);
  DESC_TYPE(unsigned long);
  DESC_TYPE(unsigned long long);

  DESC_TYPE(float);
  DESC_TYPE(double);
  DESC_TYPE(long double);

  DESC_TYPE(RegularStruct);
  DESC_TYPE(PackedStruct);
}

void demo_type_conversion()
{

  int i = 11111;
  float f = 101.9f;
  bool b = bool(i);
  std::cout << "int to bool " << b << std::endl;
  i = int(b);
  std::cout << "bool to int " << i << std::endl;
  i = int(f); // 只保留小数点前的部分
  std::cout << "float to int " << i << std::endl;
  i = 123;
  f = float(i);
  std::cout << "int to float " << f << std::endl;
  long l = 11111111111L;
  i = int(l);
  std::cout << "overflow long to int " << i << std::endl;

  unsigned int u = -84;
  std::cout << "negative unsigned int " << u << std::endl;

  u = 10;
  i = -42;
  std::cout << "negative unsigned int " << u + i << std::endl;

  unsigned u1 = 42, u2 = 10;
  std::cout << "unsigned int subtract " << u1 - u2 << std::endl;
  std::cout << "unsigned int subtract " << u2 - u1 << std::endl;

  // 不要混用signed和unsigned
}
void demo_number_leteral()
{

  unsigned u = 1u;
  long l = 100l;
  long long ll = 101ll;
  float f = 1.2f;
  long double ld = 1.3l;
  bool b = false;
  void *ptr = nullptr;

  std::cout << "literal unsigned " << u << std::endl;
  std::cout << "literal long " << l << std::endl;
  std::cout << "literal long long " << ll << std::endl;
  std::cout << "literal float " << f << std::endl;
  std::cout << "literal long double " << ld << std::endl;
  std::cout << "literal bool" << b << std::endl;
  std::cout << "literal ptr " << ptr << std::endl;
}
void demo_string_literal()
{

  // escaping chars
  // \n \v \\ \r \t \b \? \f \a \" \'
  std::cout << "\x4dO\115\n";

  char16_t c16 = u'a';
  char32_t c32 = U'a';
  wchar_t wa = L'a';
  const char *u = u8"hi!我";
  std::cout << wa << u << std::endl;
}

struct A
{
  int i;
};

/*
C++17 Standard 11.6
To default-initialize an object of type T means:
(7.1) — If T is a (possibly cv-qualified) class type (Clause 12), constructors are considered. The applicable constructors are enumerated (16.3.1.3), and the best one for the initializer () is chosen through overload resolution (16.3). The constructor thus selected is called, with an empty argument list, to initialize the object.
(7.2) — If T is an array type, each element is default-initialized.
(7.3) — Otherwise, no initialization is performed.
*/
void demo_initialization()
{
  int unit_sold1 = 0;
  int unit_sold2 = {0};
  int unit_sold3{0};
  int unit_sold4(0);

  std::cout << unit_sold1 << std::endl;
  std::cout << unit_sold2 << std::endl;
  std::cout << unit_sold3 << std::endl;
  std::cout << unit_sold4 << std::endl;

  long double ld = 3.1416;
  // int a{ld};  // 列表初始化时narrow变量会报错，无法编译，因为存在信息丢失
  std::cout << ld << std::endl;

  // 函数体内部的内置变量不会默认初始化
  int i; // random value

  std::cout << i << std::endl;

  double salary = 999.9, wage = salary; // 一行里面定义多个变量，左边定义好之后右边马上就能用了！
  std::cout << "salary = wage = " << wage << std::endl;

  A a;
  LOG(a.i); // 未初始化

  int iarr[bufsize]; // 未初始化
  describe_array(std::begin(iarr), std::end(iarr));
}
void demo_scope()
{

  int i = 100, sum = 0;

  for (int i = 0; i < 10; i++)
    sum += i;

  std::cout << i << " " << sum << std::endl;
}

void demo_compound_types()
{

  {
    int i = 1024, *p = &i, &r = i;
    std::cout << OUTPUT_VAL(i) << " "
              << OUTPUT_VAL(*p) << " "
              << OUTPUT_VAL(r) << std::endl;

    r = 42;
    std::cout << i << " " << *p << " " << r << std::endl;
  }

  {

    int i = 43;
    int *p = &i;
    int *&r = p; // 指针p的引用
    std::cout << i << " " << *p << " " << *r << std::endl;
    *r = 123;
    std::cout << i << " " << *p << " " << *r << std::endl;
  }
}

void demo_const()
{
  std::cout << "extern const " << bufsize << std::endl;
  // const reference

  int i = 1024;
  // 常量引用的值会被修改，所以const应该理解为read-only，而不是never-change
  const int &cri1 = i;
  const int ci = i;
  const int &cri2 = ci;

  std::cout << OUTPUT_VAL(i) << " "
            << OUTPUT_VAL(cri1) << " "
            << OUTPUT_VAL(ci) << " "
            << OUTPUT_VAL(cri2)
            << std::endl;
  i = 42;
  std::cout << OUTPUT_VAL(i) << " "
            << OUTPUT_VAL(cri1) << " "
            << OUTPUT_VAL(ci) << " "
            << OUTPUT_VAL(cri2)
            << std::endl;

  const int &cri3 = 43; // 常量引用可以用字面量初始化，编译器会生成一个临时常量
  std::cout << OUTPUT_VAL(cri3)
            << std::endl;
}

void demo_const_pointer()
{

  const double cd = 3.14; // top-level const
  double d = 3.15;
  double *dp = &d;
  // double *pd = &cd; error
  const double *cdp = &cd; // ok, cdp can be changed  low-level const
  // *cdp = 123.4;  // error
  cdp = nullptr; // ok
  cdp = &cd;     // ok

  double *const cp = &d; // ok, cp itself can not be changed top-level const
  // cp = nullptr;  // error
  *cp = 123.4; // ok

  const double *const cdcp = &d; // top and low-level const
  // cdcp = nullptr;  // error
  // *cdcp = 123.4;  // error
  cdp = cdcp; // 顶层const依然可以被拷贝，只要底层const合适即可。底层非const可以转成const，反之则不行
  std::cout << OUTPUT_VAL(*cdcp) << std::endl;
}

constexpr int size()
{
  return 10;
}

int get_size_in_runtime()
{
  return 42;
}

int j = 100;
constexpr int i = 42;

void demo_constexpr()
{
  /*
  常量表达式:不会改变且在编译过程就能计算结果的表达式，有两种情况
  1. 字面值（算术类型，引用，指针，字面值常量类，枚举）
  2. 用常量表达式初始化的const对象
  */
  {
    // 逻辑上的常量表达式难以分辨
    const int max_files = 20;             // yes  <=> constexpr
    const int limit = max_files + 1;      // yes  <=> constexpr
    int staff_size = 27;                  // no
    const int sz = get_size_in_runtime(); // no
  }
  constexpr int mf = 20;
  constexpr int limit = mf + 1;
  constexpr int sz = size();
  // constexpr指针都是顶层const！！！初始化后不能修改！！！和const int *ptr不一样！！！
  constexpr int *top_const = &j; // 函数体内的变量地址只能在运行时确定，constexpr指针的地址必须在编译期确定，只能用全局变量的地址。
  *top_const = 13;               // 这样是可以的，给j赋值
  // top_const = nullptr;  // error
  constexpr int *must_null = nullptr; // 否则只能用nullptr初始化
  // 底层const需要这样写，constexpr const <typename> *<pointername>  = &xxx;
  constexpr const int *cpi = &i; // 指向常量i constexpr const连写
  constexpr int *cpj = &j;       // 指向变量j
  std::cout << OUTPUT_VAL(mf) << " "
            << OUTPUT_VAL(limit) << " "
            << OUTPUT_VAL(sz) << " "
            << OUTPUT_VAL(*top_const) << " "
            << OUTPUT_VAL(*cpi) << " "
            << OUTPUT_VAL(*cpj) << std::endl;
}

void demo_typedef()
{
  typedef double wages;
  typedef wages base, *p; // p的类型是double* ....无语

  double d = 123.4;
  p xxx = &d;

  using MyDouble = double;
  using MyDoublePtr = double *;

  MyDoublePtr mdp = &d;

  typedef char *pstring;
  char s[] = "hello world";
  const pstring cstr = s; // const (char*) cstr  // 顶层const，cstr本身不能改
  const pstring *ps;      // const (char*) *ps  // 底层const，ps是指针，ps本身可以改，但指向的不能改指向的东西

  // 把const pstring cstr理解为 const char *cstr 是错的！！！

  ps = &cstr;
  std::string ss1(cstr, cstr + strlen(cstr));
  std::string ss2(*ps, *ps + strlen(*ps));

  std::cout << OUTPUT_VAL(ss1) << " " << OUTPUT_VAL(ss2) << std::endl;
}

void demo_auto()
{

  auto i = 0, *pi = &i; // 类型一致可以推理出来
  // auto sz = 0, pi = 3.14;  // 类型不一致，error

  // auto会忽略顶层const，保留底层const

  const int ci = i, &cr = ci;
  auto b = ci;  // b: int b
  auto c = cr;  // c: int c
  auto d = &i;  // d: int* d
  auto e = &ci; // e: const int* e

  // auto 明确指出顶层const
  const auto f = ci;   // 明确指出顶层const, f: const int
  const auto ff = &ci; // 明确指出顶层const, ff: const int* const

  // auto 引用类型
  auto &g = ci; // g: const &int 常量的引用
  // auto &h = 42;  // error
  const auto &h = i;  // h: const &int 明确指出常量引用
  const auto &j = 42; // j: const &int

  auto k = ci, &l = i; // k: int, l: int&
  // 引用的底层常量会自动推理出来
  auto &m = ci, *p = &ci; // m: const int&, p: const int*
  auto &n = i;            // n: int&
  auto *p2 = &ci;         // p2: const int*
}

std::string SomeFunctionReturningString()
{
  return "";
}
void demo_decltype()
{
  std::string proto("demodemodemodemo");
  decltype(SomeFunctionReturningString()) s(proto.begin(), proto.end()); // s: string
  std::cout << OUTPUT_VAL(s) << std::endl;

  // decltype的推理和auto不同。。。日
  const int ci = 0, &cj = ci;
  // decltype可以推理出顶层const和引用，而auto不能
  decltype(ci) x = 0; // x: const int
  decltype(cj) y = x; // y: const int&
  decltype(cj) z = 123;

  // 经典例子
  int i = 42, *p = &i, &r = i;
  decltype(r + 0) b;   // b: int，本来r是引用int&，但是做了个运算，就变成int了。。。
  decltype(*p) c = i;  // c: int&，因为*p是&int类型
  decltype((i)) d = i; // d: int&，decltype里的基本类型加个括号就是引用了，双层括号表示引用，记住
  decltype(i) e = 123; // e: int
}

struct SalesData
{
  std::string bookNo;      // default constructor
  unsigned units_sold = 0; // in-class initializer  =
  double revenue{0.0};     // in-class initializer  {}
  // 两种 in-class initializer都可以
}; // 注意class和struct结尾要分号;

// operator<< 重载<<运算符，第一个参数 std::ostream&，第二个自定义类型，返回类型std::ostream&
std::ostream &operator<<(std::ostream &os, const SalesData &sd)
{
  os << OUTPUT_VAL(sd.bookNo) << " " << OUTPUT_VAL(sd.units_sold) << " " << OUTPUT_VAL(sd.revenue);
  return os;
}

void custom_data_type()
{

  SalesData accum{"bbb-aaa-000", 10, 123.4}, trans, *salesPtr;

  std::cout << accum << std::endl;
}

int main(int argc, char **argv)
{
  RUN_DEMO(demo_types);
  RUN_DEMO(demo_type_conversion);
  RUN_DEMO(demo_number_leteral);
  RUN_DEMO(demo_string_literal);
  RUN_DEMO(demo_initialization);
  RUN_DEMO(demo_scope);          // {...}
  RUN_DEMO(demo_compound_types); // * &
  RUN_DEMO(demo_const);          // const
  RUN_DEMO(demo_const_pointer);  // const int*, int* const, const int* const
  RUN_DEMO(demo_constexpr);      // constexpr
  RUN_DEMO(demo_typedef);        // typedef using
  RUN_DEMO(demo_auto);           // auto
  RUN_DEMO(demo_decltype);       // decltype
  RUN_DEMO(custom_data_type);    // struct
  return EXIT_SUCCESS;
}