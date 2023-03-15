#pragma once
#include <string>
class Account
{
public:
  static double rate() { return interestRate; }
  static void rate(double);
  static double interestRate;
  static double initRate(); // static成员函数不能是const，因为static函数没有this指针

  Account() = default;
  Account(std::string o, double amt) : m_owner(o), m_amount(amt) {}
  void calculate() { m_amount = m_amount * (1.0 + interestRate); }
  const std::string &owner() { return m_owner; }
  double amount() { return m_amount; }

private:
  std::string m_owner;
  double m_amount;
  // 如果要在累的内部初始化静态成员变量，那么该静态成员必须是字面值常量
  static constexpr int period = 30;
  double daily_tbl[period]; // period可以直接用
};
