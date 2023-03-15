#include <string>
#include <iostream>
#include <memory> // 智能指针
#include <list>
#include <iomanip>
#include "utils.h"

class Car
{

public:
  Car(std::string n, std::string c, double p) : name(n), color(c), price(p) {}
  std::string name;
  std::string color;
  double price;
  static std::shared_ptr<Car> new_instance(std::string n, std::string c, double p);
};
std::shared_ptr<Car> Car::new_instance(std::string n, std::string c, double p)
{
  return std::make_shared<Car>(n, c, p);
}

std::ostream &operator<<(std::ostream &os, const Car &c)
{

  os << "Car(" << OUTPUT_MEMBER(c, name) << ", " OUTPUT_MEMBER(c, color) << ", " << OUTPUT_MEMBER(c, price) << ")";
  return os;
}

void demo_shared_ptr()
{

  std::shared_ptr<std::string> p1;
  if (!p1)
  {
    std::cout << OUTPUT_VAL(p1) << " is empty" << std::endl;
  }

  std::shared_ptr<std::list<int>> p2;
  if (!p2)
  {
    std::cout << OUTPUT_VAL(p2) << " is empty" << std::endl;
  }

  auto p3 = std::make_shared<int>(42);
  std::cout << OUTPUT_VAL(*p3) << std::endl;

  auto p4 = std::make_shared<std::string>(10, '9');
  auto p5 = std::make_shared<int>();
  auto p6 = std::make_shared<std::vector<std::string>>();

  p6->push_back("hello");
  p6->push_back("world");
  p6->push_back("yeefea");
  describe_vector(*p6);

  std::cout << OUTPUT_VAL(p6.use_count()) << std::endl;
  auto p7 = p6;
  auto p8 = p6;
  std::cout << OUTPUT_VAL(p6.use_count()) << std::endl;
  std::cout << OUTPUT_VAL(p7.use_count()) << std::endl;
  std::cout << OUTPUT_VAL(p8.use_count()) << std::endl;

  auto car1 = Car::new_instance("Audi", "Gray", 2.39909e5);
  std::cout << *car1 << std::endl;
  std::cout << OUTPUT_VAL(car1.use_count()) << std::endl;
  auto car2 = car1;
  std::cout << OUTPUT_VAL(car1.use_count()) << std::endl;
  std::cout << OUTPUT_VAL(car2.use_count()) << std::endl;
}

void demo_new()
{
  auto ps = new std::string("123123123");
  delete ps;
}

int main(int argc, char **argv)
{

  RUN_DEMO(demo_shared_ptr);
  return 0;
}