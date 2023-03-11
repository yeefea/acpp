#include "sales_data.h"
#include "utils.h"

Sales_data::Sales_data(std::istream &is)
{
  read(is, *this);
}

double Sales_data::avg_price() const
{
  if (units_sold)
  {
    return revenue / units_sold;
  }
  return 0.0;
}

Sales_data &Sales_data::combine(const Sales_data &rhs)
{
  units_sold += rhs.units_sold;
  revenue += rhs.revenue;
  return *this;
}

std::istream &read(std::istream &is, Sales_data &item)
{
  double price = 0;
  is >> item.bookNo >> item.units_sold >> price;
  item.revenue = price * item.units_sold;
  return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item)
{
  os << item.isbn() << " " << OUTPUT_VAL(item.units_sold) << " "
     << OUTPUT_VAL(item.revenue) << " " << OUTPUT_VAL(item.avg_price());
  return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
  Sales_data sum = lhs;
  return sum.combine(rhs);
}
