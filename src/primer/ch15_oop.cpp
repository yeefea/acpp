#include <iostream>
#include "ch15_oop.h"
#include "quote.h"
#include "utils.h"
#include "basket.h"

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

void demo_virtual_func_scope()
{
  Base1 bobj;
  D1 d1obj;
  D2 d2obj;

  Base1 *bp1 = &bobj;
  Base1 *bp2 = &d1obj;
  Base1 *bp3 = &d2obj;

  D1 *d1p = &d1obj;
  D2 *d2p = &d2obj;

  bp1->fcn();
  bp2->fcn();
  bp3->fcn();

  // bp2->f2();
  d1p->f2();
  d2p->f2();

  D1 *p1 = &d2obj;
  D2 *p2 = &d2obj;

  p1->fcn(1); // 静态绑定，非虚函数，调用D1::
  p2->fcn(1); // 静态绑定，非虚函数，调用D2::

  D3 d3obj;
  d3obj.fcn();
}

void demo_virtual_destructor()
{
  /*
  As a guideline, any time you have a virtual function in a class,
  you should immediately add a virtual destructor (even if it does nothing).
  This way, you ensure against any surprises later.
  */
  ObjVirtualDestructor *obj = new DerivedObjVirtualDestructor();
  delete obj;
}

void demo_copy_control()
{
}

void demo_inheriting_constructor()
{
  ObjConstructor obj(1, "333");
  obj.describe(std::cout);
  std::cout << std::endl;

  DerivedObjConstructor dobj(4, "123");
  ObjConstructor &robj = dobj;

  robj.describe(std::cout);
  std::cout << std::endl;

  dobj = DerivedObjConstructor(2, "111", 3);
  robj.describe(std::cout);
}
void demo_container_inheritance()
{
  // （智能）指针实现容器里存放多种类型
  std::vector<std::shared_ptr<Quote>> basket;

  for (int i = 0; i < 10; ++i)
  {
    basket.push_back(std::make_shared<BulkQuote>("123123", 50, 10, 0.01 * i));
  }

  for (int i = 0; i < 10; ++i)
  {
    for (int j = 5; j < 15; ++j)
    {
      std::cout << basket[i]->net_price(j) << std::endl;
    }
  }
}
void demo_basket()
{
  Basket bskt;
  bskt.add_item(std::make_shared<Quote>("123123", 45));
  bskt.add_item(std::make_shared<BulkQuote>("123123", 45, 2, 0.3));
  bskt.add_item(std::make_shared<BulkQuote>("123123", 45, 2, 0.3));
  bskt.add_item(std::make_shared<BulkQuote>("123123", 45, 2, 0.3));
  bskt.add_item(std::make_shared<BulkQuote>("1231234", 45, 10, 0.2));

  bskt.total_receipt(std::cout);
}

int main(int argc, char **argv)
{
  RUN_DEMO(demo_type_conversion);
  RUN_DEMO(demo_virtual_function);
  RUN_DEMO(demo_default_argument);
  RUN_DEMO(demo_abstract_base_class);
  RUN_DEMO(demo_access);
  RUN_DEMO(demo_virtual_func_scope);
  RUN_DEMO(demo_virtual_destructor);
  RUN_DEMO(demo_copy_control);
  RUN_DEMO(demo_inheriting_constructor);
  RUN_DEMO(demo_container_inheritance);
  RUN_DEMO(demo_basket);
  return EXIT_SUCCESS;
}
