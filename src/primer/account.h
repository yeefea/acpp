#pragma once
#include <string>
class Account
{
public:
  void calculate() { amount = amount * (1.0 + interestRate); }
  static double rate() { return interestRate; }
  static void rate(double);

private:
  std::string owner;
  double amount;
  static double interestRate;
  static double initRate();
};

// 类外部不用static
double Account::initRate()
{
  return 0.05;
}

double Account::interestRate = initRate();

// 类外部不用static
void Account::rate(double newRate)
{
  interestRate = newRate;
}
