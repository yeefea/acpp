#include "ch16_template.h"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <list>
#include <memory>
#include <type_traits>
#include <vector>

#include "blob.h"
#include "utils.h"

// 问题：类模板的成员模板怎么显式实例化？
// 显式实例化
// 实例化声明，在ch16_template_instance.cpp中实例化
extern template int compare(const int &, const int &);

void demo_function_template() {
  auto cmp_res = compare(1, 2);
  std::cout << OUTPUT_VAL(cmp_res) << std::endl;

  cmp_res = compare<double>(3.0, 1);
  std::cout << OUTPUT_VAL(cmp_res) << std::endl;

  cmp_res = compare<char>('a', 'a');
  std::cout << OUTPUT_VAL(cmp_res) << std::endl;

  cmp_res = compare_arr("hello", "world");
  std::cout << OUTPUT_VAL(cmp_res) << std::endl;

  auto res = play_constexpr_template(1);
  std::cout << OUTPUT_VAL(res) << std::endl;
}

void demo_class_template() {
  Blob<int> ia;
  ia.describe(std::cout);
  Blob<int> ia2 = {0, 1, 2, 3, 4, 5};
  ia2.describe(std::cout);

  auto ifront = ia2.front();
  auto iback = ia2.back();

  std::cout << OUTPUT_VAL(ifront) << ", " << OUTPUT_VAL(iback) << std::endl;
}

void demo_template() {
  std::shared_ptr<std::vector<std::string>> pvs =
      std::make_shared<std::vector<std::string>>();
  pvs->push_back("123123");
  pvs->push_back("1231233333");
  describe_vector(*pvs);
}

// 模板类型别名
// 1.
typedef Blob<std::string> StrBlob;

// 2.
template <typename T>
using twin = std::pair<T, T>;

// 3.
template <typename T>
using PartNo = std::pair<T, unsigned>;

void demo_template_alias() {
  StrBlob sb;
  twin<int> ii = {1, 2};
  PartNo<std::string> pp = {"123123", 1};
}

void demo_template_static_member() {}

void demo_template_default_params() {
  Numbers<long double> ddd(0.123);
  Numbers<> iii(123);  // 总是需要尖括号
}

void demo_member_template() {
  // 成员模板不能是虚函数！！！

  std::unique_ptr<int, DebugDelete> p(new int, DebugDelete());

  std::unique_ptr<std::string, DebugDelete> sp(new std::string, DebugDelete());

  std::list<const char *> w = {"now", "is", "the", "time"};

  Blob2<std::string> a3(w.begin(), w.end());
}

void demo_type_deduction() {
  std::vector<int> vi = {1, 2, 3, 4, 5};
  auto &i = fcn(vi.begin(), vi.end());

  std::cout << OUTPUT_VAL(i) << std::endl;
}

void demo_type_traits() {
  int i = 123;
  int *pi = &i;
  std::remove_reference<decltype(*pi)>::type x;  // x is int..... nb...

  std::vector<int> vi = {1, 2, 3, 4, 5};
  i = fcn2(vi.begin(), vi.end());
  std::cout << OUTPUT_VAL(i) << std::endl;
  std::remove_pointer<int *>::type ii = 1;
}

// 函数指针，实参推断，很神奇。。。自动推出了compare<int>
int (*pf1)(const int &, const int &) = compare;

auto pf2 = compare<int>;

// 左值引用推断
template <typename T>
void f(T &p) {
  std::cout << OUTPUT_VAL(p) << std::endl;
}

template <typename T>
void f2(const T &cp) {
  std::cout << OUTPUT_VAL(cp) << std::endl;
}

// 右值引用推断
template <typename T>
void f3(T &&rr) {
  std::cout << OUTPUT_VAL(rr) << std::endl;
}

void demo_type_argument_deduction() {
  int i = 1;
  f(i);  // f<int>

  const int ci = 13;
  f(ci);  // f<const int>

  // f(4);  error 左值引用不接受字面量

  f2(4);  // f2<int>

  f3(42);  // f3<int>

  f3(i);  // f3<int&>引用折叠
}

int main(int argc, char **argv) {
  RUN_DEMO(demo_function_template);
  RUN_DEMO(demo_class_template);
  RUN_DEMO(demo_template);
  RUN_DEMO(demo_template_alias);
  RUN_DEMO(demo_template_static_member);
  RUN_DEMO(demo_template_default_params);
  RUN_DEMO(demo_member_template);
  RUN_DEMO(demo_type_deduction);
  RUN_DEMO(demo_type_traits);
  RUN_DEMO(demo_type_argument_deduction);
  return EXIT_SUCCESS;
}