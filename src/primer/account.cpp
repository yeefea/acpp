#include "account.h"

// 类外部不用static
double Account::initRate()
{
  return 0.05;
}

// 类外部定义静态成员变量不能重复static关键字
double Account::interestRate = initRate(); // 定义静态成员变量

// 类外部定义静态成员函数不能重复static关键字
void Account::rate(double newRate) // 定义静态成员函数
{
  interestRate = newRate;
}
