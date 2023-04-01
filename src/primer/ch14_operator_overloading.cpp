#include <iostream>
#include <cstdint>
#include "utils.h"
#include "ch14_operator_overloading.h"

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
}

int main(int argc, char **argv)
{
  RUN_DEMO(demo_operator);

  return 0;
}