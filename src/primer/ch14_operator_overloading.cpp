#include <iostream>
#include <cstdint>
#include <functional>
#include <map>
#include "utils.h"
#include "ch14_operator_overloading.h"

// IO运算符必须是非成员函数
std::ostream &operator<<(std::ostream &os, const SalesData &item)
{
  os << OUTPUT_MEMBER(item, isbn) << ", " << OUTPUT_MEMBER(item, units_sold) << ", " << OUTPUT_MEMBER(item, average_price());
  return os;
}

SalesData operator+(const SalesData &lhs, const SalesData &rhs)
{
  return SalesData(lhs.isbn, lhs.units_sold + rhs.units_sold, lhs.revenue + rhs.revenue);
}

bool operator==(const SalesData &lhs, const SalesData &rhs)
{
  return lhs.isbn == rhs.isbn && lhs.units_sold == rhs.units_sold && lhs.revenue == rhs.revenue;
}

MyInt operator+(const MyInt &lhs, const MyInt &rhs)
{
  MyInt ret(lhs.i + rhs.i);
  return ret;
}

std::ostream &operator<<(std::ostream &os, const MyInt &rhs)
{
  os << rhs.i;
  return os;
}

MyInt operator<<(const MyInt &lhs, const MyInt &rhs)
{
  return MyInt(lhs.i << rhs.i);
}

void demo_operator()
{
  std::string s1 = "123", s2 = "abc";

  std::string s3 = operator+(s1, s2); // explicit调用运算符
  s2.operator+=(s3);                  // member function

  std::cout << OUTPUT_VAL(s2) << " " << OUTPUT_VAL(s3) << std::endl;

  std::string s(s1);
  SalesData item0(s);
  SalesData item{"123123-111", 10, 20.3};
  std::cout << item << std::endl;

  MyInt i(10);
  std::cout << OUTPUT_VAL(i) << ", " << OUTPUT_VAL(i << MyInt(3)) << std::endl;

  DemoEvilOperator evil;
  auto evil_res1 = *evil;
  auto evil_res2 = evil.operator->();
  std::cout << OUTPUT_VAL(evil_res1) << ", " << OUTPUT_VAL(evil_res2) << std::endl;
}

void demo_lambda()
{
}
void demo_functional()
{
  std::plus<int> addInt;
  auto res = addInt(1, 2);
  std::cout << OUTPUT_VAL(res) << std::endl;
}

int add(int a, int b)
{
  return a + b;
}

struct divide
{
  int operator()(int a, int b)
  {
    return a / b;
  }
};

auto mod = [](int a, int b)
{ return a % b; };

void demo_function()
{

  std::map<std::string, std::function<int(int, int)>> op_table;
  op_table["+"] = add;
  op_table["%"] = mod;
  op_table["/"] = divide();

  std::function<int(int, int)> a = op_table["+"];
  auto res = a(1, 3);
  std::cout << OUTPUT_VAL(res) << std::endl;
}

void ambiguous_conversion(A aobj)
{
  // pass
}

void demo_type_conversion()
{

  SmallInt si = 10;
  int converted = static_cast<int>(si);
  std::cout << OUTPUT_VAL(converted) << std::endl;

  si = 42;
  converted = si.operator int();
  std::cout << OUTPUT_VAL(converted) << std::endl;

  B bobj;
  // ambiguious_conversion(bobj);  ambiguous
  ambiguous_conversion(A(bobj));
  ambiguous_conversion(bobj.operator A());
}

int main(int argc, char **argv)
{
  RUN_DEMO(demo_operator);
  RUN_DEMO(demo_lambda);
  RUN_DEMO(demo_functional);
  RUN_DEMO(demo_function);
  RUN_DEMO(demo_type_conversion);
  return 0;
}