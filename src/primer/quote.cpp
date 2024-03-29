#include "quote.h"

BulkQuote::BulkQuote(const std::string &book, double p, std::size_t qty, double disc)
    : Quote(book, p), min_qty(qty), discount(disc) {} // 调用父类构造函数
double print_total(std::ostream &os, const Quote &item, std::size_t n)
{
  double ret = item.net_price(n);
  os << "ISBN: " << item.isbn() << " # sold: " << n << ", total due: " << ret << std::endl;
  return ret;
}

double BulkQuote::net_price(size_t cnt) const
{

  if (cnt >= min_qty)
  {
    return cnt * (1 - discount) * price;
  }
  else
  {
    return Quote::net_price(cnt);
  }
}