#pragma once

#include <cstddef>
#include <string>
#include <iostream>

class Quote
{
public:
  Quote() = default;
  Quote(const Quote &q) : book_no(q.book_no), price(q.price) {}
  Quote(const std::string &book, double sales_price) : book_no(book), price(sales_price) {}
  // 图书编号
  std::string isbn() const { return book_no; }
  // 实际销售价格
  virtual double net_price(std::size_t n) const
  {
    return n * price;
  }
  virtual ~Quote() = default; // 析构函数一般都要定义为virtual

  virtual Quote *clone() const &
  {
    return new Quote(*this);
  }
  virtual Quote *clone() &&
  {
    return new Quote(std::move(*this));
  }

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
  virtual BulkQuote *clone() const & override
  {
    return new BulkQuote(*this);
  }
  virtual BulkQuote *clone() && override
  {
    return new BulkQuote(std::move(*this));
  }

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

double print_total(std::ostream &os, const Quote &item, std::size_t n);