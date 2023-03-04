#include <iostream>
#include <cstdlib>
#include "sales_data.h"
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

  double salary = 999.9, wage = salary;
  std::cout << "salary = wage = " << wage << std::endl;
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

  const double cd = 3.14;
  double d = 3.15;
  double *dp = &d;
  // double *pd = &cd; error
  const double *cdp = &cd; // ok, cdp can be changed
  // *cdp = 123.4;  // error
  cdp = nullptr; // ok
  cdp = &cd;     // ok

  double *const cp = &d; // ok, cp itself can not be changed
  // cp = nullptr;  // error
  *cp = 123.4; // ok

  const double *const cdcp = &d;
  // cdcp = nullptr;  // error
  // *cdcp = 123.4;  // error
  std::cout << OUTPUT_VAL(*cdcp) << std::endl;
}

int main(int argc, char **argv)
{
  RUN_DEMO(demo_types);
  RUN_DEMO(demo_type_conversion);
  RUN_DEMO(demo_number_leteral);
  RUN_DEMO(demo_string_literal);
  RUN_DEMO(demo_initialization);
  RUN_DEMO(demo_scope);
  RUN_DEMO(demo_compound_types);
  RUN_DEMO(demo_const);
  RUN_DEMO(demo_const_pointer);
  return EXIT_SUCCESS;
}