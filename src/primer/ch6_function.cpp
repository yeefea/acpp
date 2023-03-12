#include <iostream>
#include <string>
#include <initializer_list>
#include <cstdlib>
#include <cstdarg>
#include "utils.h"

// inline函数和constexpr都应该放在.h文件里

int counter()
{
  static int x = 0; // 局部静态对象
  return x++;
}

void func_with_arr_param1(const int *)
{
}

void func_with_arr_param2(const int[])
{
}
void func_with_arr_param3(const int[11111])
{ // 形参里的数组长度是没有用的!!!很有迷惑性!!!
}
void init_arr(int (&arr)[10])
{
  // 形参里的数组长度是有用的!!!
  for (auto &elem : arr)
  {
    elem = 42;
  }
}

template <typename T>
void describe_values(std::initializer_list<T> lst)
{
  for (auto iter = lst.begin(); iter != lst.end(); ++iter)
  {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;
}
const std::string &shorter_string(const std::string &s1, const std::string &s2)
{
  return s1.size() < s2.size() ? s1 : s2;
}

std::string &shorter_string(std::string &s1, std::string &s2)
{
  // const转型
  auto &r = shorter_string(const_cast<const std::string &>(s1), const_cast<const std::string &>(s2));
  return const_cast<std::string &>(r);
}

int add(int a, int b)
{
  return a + b;
}

auto tail_return() -> int (*)(int, int)
{
  // 返回函数指针
  return add;
}

void demo_function()
{
  constexpr int arr_size = 10;
  // local static
  for (int i = 0; i < arr_size; ++i)
  {
    std::cout << OUTPUT_VAL(counter()) << std::endl;
  }

  int arr[arr_size];

  func_with_arr_param1(arr);
  func_with_arr_param2(arr);
  func_with_arr_param3(arr);
  init_arr(arr);
  describe_array(arr, arr + arr_size);

  // initialize_list
  describe_values({1, 2, 3, 4, 5});

  // tailing return type
  auto add1 = tail_return();
  decltype(tail_return) *fp;
  fp = tail_return;
  auto res = add1(1, 3);
  std::cout << OUTPUT_VAL(res) << std::endl;
}

constexpr int new_sz() { return 42; }

constexpr int cadd(int a, int b)
{
  return a + b;
}

void demo_constexpr_func()
{
  constexpr int sz = new_sz();
  std::cout << OUTPUT_VAL(sz) << std::endl;

  constexpr int num1 = 1, num2 = 2;
  constexpr int res = cadd(num1, num2);

  std::cout << OUTPUT_VAL(num1) << ", " << OUTPUT_VAL(num2) << ", " << OUTPUT_VAL(res) << std::endl;
}

int main(int argc, char **argv)
{
  RUN_DEMO(demo_function);
  RUN_DEMO(demo_constexpr_func);
  return EXIT_SUCCESS;
}