#include <iostream>
#include "ch15_oop.h"
#include "utils.h"

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

void demo_type_conversion()
{
  // 只有指针和引用能转换，值类型不能转换
  BulkQuote bulk("123123-1111", 100, 3, 0.1);
  Quote *qp = &bulk;
  BulkQuote *bp = static_cast<BulkQuote *>(qp);  // 强制转换
  BulkQuote &br = static_cast<BulkQuote &>(*qp); // 强制转换
  // CSV
  std::cout << "n,value" << std::endl;
  for (auto n : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10})
  {
    auto value = qp->net_price(n);
    std::cout << n << "," << value << std::endl;
  }

  // 下面这样初始化是调用了基类的拷贝构造函数，子类的信息被sliced down了
  Quote qvalue = BulkQuote("12312", 100, 3, 0.1);
  for (auto n : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10})
  {
    auto value = qvalue.net_price(n);
    std::cout << n << "," << value << std::endl;
  }

  Quote &qref = bulk; // 这样是可以的，不会被slice down
  for (auto n : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10})
  {
    auto value = qref.net_price(n);
    std::cout << n << "," << value << std::endl;
  }
}

void demo_virtual_function()
{
  // polymorphism

  // 虚函数
  Quote base("0-201-23452-1", 50);
  print_total(std::cout, base, 10);
  BulkQuote derived("0-201-23452-1", 50, 5, .19);
  print_total(std::cout, derived, 10);

  // 强行调用基类的函数
  Quote *bp = &derived;
  auto np = bp->Quote::net_price(42);
  std::cout << OUTPUT_VAL(bp->net_price(42)) << ", " << OUTPUT_VAL(np) << std::endl;

  Quote &br = derived;
  np = br.Quote::net_price(43);
  std::cout << OUTPUT_VAL(bp->net_price(43)) << ", " << OUTPUT_VAL(np) << std::endl;

  base = derived; // 普通类型只是拷贝，无法实现动态绑定
  print_total(std::cout, base, 10);
}

void demo_default_argument()
{
  D derived;

  B &br = derived;
  D &dr = derived;

  // 由静态类型决定
  br.get_ptr(); // i=1
  dr.get_ptr(); // i=2
}

double BulkQuote2::net_price(std::size_t n) const
{
  return Quote::net_price(n) * (1.0 - discount);
}

void demo_abstract_base_class()
{
  // DiscQuote q; // DiscQuote有纯虚函数，不能实例化，和Java一样
  BulkQuote2 q2("123123", 100.0, 10, 0.13);

  auto disc_price = q2.net_price(1);
  std::cout << OUTPUT_VAL(disc_price) << std::endl;
}

void demo_access()
{
  // public
  // protected
  // private
  // friend关系不能继承，每个类设置自己的friend

  PubDeriv pub;
  ProtDeriv prot;
  PrivDeriv priv;

  Base &br_pub = pub; // public derive可以上转型

  // Base &br_prot = prot; protected和private derive都不能上转型
  // Base &br_priv = priv;
}

int main(int argc, char **argv)
{
  RUN_DEMO(demo_type_conversion);
  RUN_DEMO(demo_virtual_function);
  RUN_DEMO(demo_default_argument);
  RUN_DEMO(demo_abstract_base_class);
  RUN_DEMO(demo_access);
  return EXIT_SUCCESS;
}
