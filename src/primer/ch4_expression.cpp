#include <iostream>
#include <string>
#include "utils.h"

void demo_arithmetic_op()
{
  // +n -n
  // a*b a/b a%b
  // a+b a-b
  // 如果m%n的结果不等于0，则符号与m相同，m=(m/n)*n+m%n恒成立
  std::cout << OUTPUT_VAL(21 % 6) << ", " << OUTPUT_VAL(21 / 6) << std::endl;
  std::cout << OUTPUT_VAL(21 % 7) << ", " << OUTPUT_VAL(21 / 7) << std::endl;
  std::cout << OUTPUT_VAL(21 % 8) << ", " << OUTPUT_VAL(21 / 8) << std::endl;     // 5
  std::cout << OUTPUT_VAL(21 % -8) << ", " << OUTPUT_VAL(21 / -8) << std::endl;   // 5
  std::cout << OUTPUT_VAL(-21 % -8) << ", " << OUTPUT_VAL(-21 / -8) << std::endl; //-5
  std::cout << OUTPUT_VAL(21 % -5) << ", " << OUTPUT_VAL(21 / -5) << std::endl;   // 1
}
void demo_logic_op()
{
  // !a
  // a<b a<=b a>b a>=b
  // a==b a!=b
  // a&&b
  // a||b
}

void demo_assign_op()
{
  // = += -= *= /= %= <<= >>= &= ^= |=
  int i = 0, j = 0, k = 0;
  k = 1;
  k = 3.14; // 隐式转换
  k = {2};  // 初始值列表用于赋值
  // k = {3.14};  // 错！初始化列表不能narrowing

  // assignment 右结合
  int ival, jval;
  ival = jval = 123;
  std::cout << OUTPUT_VAL(ival) << " " << OUTPUT_VAL(jval) << std::endl;

  std::vector<int> vi;
  vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  describe_vector(vi);
}

void demo_incr_op()
{
  int i = 0, j1, j2;
  // 优先用前置++ --运算符!
  j1 = ++i;
  j2 = i++;
  std::cout << OUTPUT_VAL(j1) << " " << OUTPUT_VAL(j2) << std::endl;

  // 后置++的经典用法
  std::vector<int> vi = {1, 2, 3, 4, 5, 6};
  auto pbeg = vi.begin();
  while (pbeg != vi.end() && *pbeg >= 0)
  {
    std::cout << *pbeg++ << " ";
  }
  std::cout << std::endl;
}

void demo_member_op()
{

  std::string s1 = "123456 7";
  auto p = &s1;

  std::string::size_type sz = p->size();
}

void demo_condition_op()
{

  int grade = 59;
  // pred ? expr1 : expr2
  // 只会对expr1,expr2其中一个求值
  std::string finalgrade = (grade < 60) ? "fail" : "pass";
  std::cout << OUTPUT_VAL(grade) << ", " << OUTPUT_VAL(finalgrade) << std::endl;

  grade = 60;
  // 嵌套，右结合
  std::string finalgrade2 = (grade > 90)
                                ? "high pass"
                            : (grade < 60)
                                ? "fail"
                                : "pass";
  std::cout << OUTPUT_VAL(grade) << ", " << OUTPUT_VAL(finalgrade2) << std::endl;

  std::string finalgrade3 = (grade > 90)
                                ? "high pass"
                                : ((grade < 60)
                                       ? "fail"
                                       : "pass"); // 等价于上面的表达式
  std::cout << OUTPUT_VAL(grade) << ", " << OUTPUT_VAL(finalgrade3) << std::endl;

  // condition运算符优先级很低，要加括号
  std::cout << ((grade < 60) ? "fall" : "pass") << std::endl;
}

void demo_bit_op()
{
  // ~ not
  // << >>  left right
  // & and
  // ^ xor
  // | or
}
void demo_sizeof_op()
{
  // 两种用法
  // sizeof(type) 对类型使用
  // sizeof expr  对表达式使用

  long long llll = 1000LL;
  std::cout << OUTPUT_VAL(sizeof(long long)) << std::endl; // 对类型使用
  std::cout << OUTPUT_VAL(sizeof llll) << std::endl;       // 对表达式使用

  std::string data("123456789000000");
  std::string *p = nullptr; // 没问题!完全正确
  std::cout << OUTPUT_VAL(sizeof p) << std::endl;
  // sizeof和*优先级相同，sizeof右结合
  std::cout << OUTPUT_VAL(sizeof *p) << " is equivalent to " << OUTPUT_VAL(sizeof(*p)) << std::endl;

  struct some_struct
  {
    int field1;
    char field2;
  };

  struct some_packed_struct
  {
    int field1;
    char field2;
  } __attribute__((packed));

  std::cout << OUTPUT_VAL(sizeof some_struct::field1) << std::endl;
  std::cout << OUTPUT_VAL(sizeof some_struct::field2) << std::endl;
  std::cout << OUTPUT_VAL(sizeof(some_struct)) << std::endl;
  std::cout << OUTPUT_VAL(sizeof(some_packed_struct)) << std::endl;

  int ia[] = {123, 4, 5, 6, 7, 7, 8, 9, 10};
  constexpr size_t sz = sizeof(ia) / sizeof(*ia);
  std::cout << "size of ia: " << OUTPUT_VAL(sz) << std::endl;
}

void demo_comma_op()
{
  std::vector<int> ivec(10, 3);
  describe_vector(ivec);
  std::vector<int>::size_type cnt = ivec.size();
  for (decltype(ivec)::size_type ix = 0; ix != ivec.size(); ++ix, --cnt)
  {
    ivec[ix] = cnt;
  }

  describe_vector(ivec);
}

void demo_type_conversion()
{
  // implicit conversion
  // integer promotion
  // bool/char/signed char/unsigned char -> int
  // wchar_t/char16_t/char32_t -> int/unsigned int/long/unsigned long/long long/unsigned long long
  bool flag = true;
  char cval = 'a';
  short sval = 1;
  unsigned short usval = 2;
  int ival = 3;
  unsigned int uival = 4U;
  long lval = 5L;
  unsigned long ulval = 6UL;
  float fval = 7.1f;
  double dval = 8.2;
  std::cout << OUTPUT_VAL(3.14159L + 'a') << std::endl;
  std::cout << OUTPUT_VAL(dval + ival) << std::endl;
  std::cout << OUTPUT_VAL(dval + fval) << std::endl;
  ival = dval;
  std::cout << OUTPUT_VAL(ival) << std::endl;
  fval = dval;
  std::cout << OUTPUT_VAL(fval) << std::endl;
  std::cout << OUTPUT_VAL(cval + fval) << std::endl;
  std::cout << OUTPUT_VAL(sval + cval) << std::endl;
  std::cout << OUTPUT_VAL(cval + lval) << std::endl;
  std::cout << OUTPUT_VAL(ival + ulval) << std::endl;
  std::cout << OUTPUT_VAL(usval + ival) << std::endl;
  std::cout << OUTPUT_VAL(uival + lval) << std::endl;

  // explicit conversion
  // static_cast<typename>(xxx)
  // dynamic_cast<typename>(xxx)
  // const_cast<typename>(xxx)  只能改变常量属性
  // reinterpret_cast<typename>(xxx)

  // static_cast
  int i = 10;
  double d = static_cast<double>(i);

  void *p = &d;
  double *dp = static_cast<double *>(p);

  // const_cast
  char ch[] = {'a', 'b', 'c', '\0'};
  const char *const_pc = ch;
  char *pc = const_cast<char *>(const_pc);
  *pc = 'z';
  std::cout << ch << std::endl;

  // reinterpret_cast
  int *ip = &i;
  pc = reinterpret_cast<char *>(ip);

  for (auto i = 0; i < sizeof *ip; ++i)
  {
    std::cout << int(*(pc + i)) << " ";
  }
  std::cout << std::endl;

  // 旧的强制转换
  // type(expr)
  // (type)expr C语言风格
  char *pc2 = (char *)ip;  // 等价于reinterpret_cast
}
int main(int argc, char **argv)
{
  RUN_DEMO(demo_arithmetic_op);
  SKIP_RUN_DEMO(demo_logic_op);
  RUN_DEMO(demo_assign_op);
  RUN_DEMO(demo_incr_op);
  SKIP_RUN_DEMO(demo_member_op);
  RUN_DEMO(demo_condition_op);
  SKIP_RUN_DEMO(demo_bit_op);
  RUN_DEMO(demo_sizeof_op);
  RUN_DEMO(demo_comma_op);
  RUN_DEMO(demo_type_conversion);
  return EXIT_SUCCESS;
}
