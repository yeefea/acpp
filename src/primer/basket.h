#pragma once
#include <memory>
#include <set>
#include <iostream>

#include "quote.h"

class Basket
{
public:
  void add_item(const std::shared_ptr<Quote> &sale)
  {
    items.insert(sale);
  }

  void add_item(const Quote &sale)
  {
    items.insert(std::shared_ptr<Quote>(sale.clone()));
  }
  void add_item(Quote &&sale)
  {
    items.insert(std::shared_ptr<Quote>(std::move(sale).clone())); // sale本身是左值
  }
  double total_receipt(std::ostream &) const;

private:
  // 类成员
  static bool compare(const std::shared_ptr<Quote> &lhs,
                      const std::shared_ptr<Quote> &rhs)
  {
    return lhs->isbn() < rhs->isbn();
  }

  std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items{compare};
};