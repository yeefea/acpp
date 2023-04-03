#pragma once

#include <string>
#include <cstddef>
#include "utils.h"

class Quote
{
public:
  Quote() = default;
  Quote(const Quote &q) : book_no(q.book_no), price(q.price) {}
  Quote(const std::string &book, double sales_price) : book_no(book), price(sales_price) {}
  std::string isbn() const { return book_no; }
  virtual double net_price(std::size_t n) const
  {
    return n * price;
  }
  virtual ~Quote() = default; // 析构函数一般都要定义为virtual

private:
  std::string book_no;

protected:
  double price = 0.0;
};

class BulkQuote; // 声明子类的时候不能写派生列表

class BulkQuote : public Quote // 被用作基类的类必须已经被定义
{
public:
  BulkQuote() = default;
  BulkQuote(const std::string &, double, std::size_t, double);
  double net_price(std::size_t n) const override; // override关键字，顺序：const && override
private:
  std::size_t min_qty = 0; // 最小批发量
  double discount = 0.0;   // 折扣
};

class DiscQuote : public Quote
{

public:
  DiscQuote() = default;
  DiscQuote(const std::string &s, double p, std::size_t q, double disc)
      : Quote(s, p), quantity(q), discount(disc) {}
  double net_price(std::size_t) const override = 0;

protected:
  std::size_t quantity = 0;
  double discount = 0.0;
};

class BulkQuote2 : DiscQuote
{
public:
  BulkQuote2() = default;
  BulkQuote2(const std::string &s, double p, std::size_t q, double disc)
      : DiscQuote(s, p, q, disc) {}
  double net_price(std::size_t n) const override; // override关键字，顺序：const && override
};

// final 关键字
class NoDerived final // final类不能作为基类，和Java一样
{
};

class Base
{
public:
  int m_pub;

protected:
  int m_prot;

private:
  int m_priv;
};

class Last final : Base
{
};

// class Bad : Last  // 错误，last是final类，不能被继承
// {
// };

class B
{
public:
  virtual B &get_ptr(int i = 1)
  {
    std::cout << OUTPUT_VAL(i) << std::endl;
    return *this;
  }

  virtual int final_func() final
  {
    return 10;
  }
};

class D : public B
{
public:
  // 运行时使用的实参由静态类型决定！！！不是动态类型！！！
  D &get_ptr(int i = 2) override final // 参数必须完全一致，但是返回类型可以是子类，override关键字是为了防止写错，让编译器检查
  {
    std::cout << OUTPUT_VAL(i) << std::endl;
    return *this;
  }
};

class E : public B
{
public:
  // int final_func() override // 错误，无法重写final函数
  // {
  // }
};

class PubDeriv : public Base
{

  void some_func()
  {
    m_prot = 1;
    m_pub = 2;
    // m_priv = 3; inaccessable
  }
};

class ProtDeriv : protected Base
{
  void some_func()
  {
    m_prot = 1;
    m_pub = 2;
    // m_priv = 3;
  }
};

class PrivDeriv : private Base
{
  void some_func()
  {
    m_prot = 1;
    m_pub = 2;
    // m_priv = 3;

    Base &br = *this; // ok
  }
};

class PrivDeriv2 : private Base
{

protected:
  using Base::m_pub; // using可以改变可访问性，子类又能访问了
};

class DerivePubDerive : public PubDeriv
{
  void some_func()
  {
    m_prot = 1;
    m_pub = 2;
    // m_priv = 3;
  }
};

class DeriveProtDerive : public ProtDeriv
{
  void some_func()
  {
    m_prot = 1; // protected
    m_pub = 2;  // protected
    // m_priv = 3;
    Base &br = *this; // ok
  }
};

class DerivePrivDerive : public PrivDeriv
{
  void some_func()
  {
    // 啥都访问不了
    // m_prot = 1;
    // m_pub = 2;
    // m_priv = 3;

    // Base &br = *this; // 父类是private继承，不能把上转型为Base了
    PrivDeriv &pr = *this; // 这是可以的
  }
};

class DerivePriveDerive2 : public PrivDeriv2
{
  void some_func()
  {
    // m_prot = 1;
    m_pub = 2; // 虽然父类是private继承，但是父类指定了m_pub为protected，这里可以访问
    // m_priv = 3;

    // Base &br = *this; // 父类是private继承，不能把上转型为Base了
  }
};

class DefaultDeriveClass : Base
{
  // <=> : private Base
};

struct DefaultDeriveStruct : Base
{
  // <=> : public Base
};