#pragma once

class SalesData
{

public:
  std::string isbn;
  int units_sold;
  double revenue;
  // 所有单参数的构造函数都必须是显示的，只有极少数情况下拷贝构造函数可以不声明称explicit。例如作为其他类的透明包装器的类。
  explicit SalesData(std::string isbn) : isbn(isbn) {}
  SalesData(std::string isbn, int units_sold, double revenue) : isbn(isbn), units_sold(units_sold), revenue(revenue) {}
  double average_price() const { return revenue / units_sold; }
};

std::ostream &operator<<(std::ostream &os, const SalesData &item);

SalesData operator+(const SalesData &lhs, const SalesData &rhs);

bool operator==(const SalesData &lhs, const SalesData &rhs);

class MyInt
{

public:
  int i;
  explicit MyInt(int i) : i(i) {}
};

MyInt operator+(const MyInt &lhs, const MyInt &rhs);

std::ostream &operator<<(std::ostream &os, const MyInt &rhs);

MyInt operator<<(const MyInt &lhs, const MyInt &rhs);