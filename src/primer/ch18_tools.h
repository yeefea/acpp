#pragma once
#include <initializer_list>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

// 函数try语句块
template <typename T>
class DemoConstructorObj {
 public:
  DemoConstructorObj(std::initializer_list<T> il) try
      : data(std::make_shared<std::vector<T>>(il)) {
    throw std::runtime_error("construct failed");
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
    // 注意，构造函数这里就算catch了异常，还是会重新抛出
  }

  ~DemoConstructorObj() try {
    throw std::runtime_error("destruct failed");
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }

 private:
  std::shared_ptr<std::vector<T>> data;
};

void function_with_try_block() try {
  std::cout << "demo function-try block" << std::endl;
  throw std::runtime_error("function_with_try_block failed");
} catch (const std::exception &e) {
  std::cout << e.what() << std::endl;
}

class MyError : public std::runtime_error {
 public:
  explicit MyError(const std::string &s) : std::runtime_error(s) {}
};

namespace A {
class C {
  // 未声明的类或函数第一次出现在friend声明中，成为最近的外层namespace的成员
  friend void f2();
  friend void f(const C &);
};

}  // namespace A
void A::f(const A::C &) {}
void A::f2() {}

namespace NS {
class Quote {};
void display(const Quote &) {
  std::cout << "display() is in namespace NS" << std::endl;
}
}  // namespace NS

class BulkItem : public NS::Quote {};

namespace p1 {
int print(int i) { return i; }
}  // namespace p1

namespace p2 {
int print(int i, int j) { return i + j; }
double print(double i, double j) { return i + j; }
}  // namespace p2

// multi-inheritance
class ZooAnimal {};
class Endangered {
 public:
  std::string name;
  static int critical;
  explicit Endangered(int l) : level(l) {}

 private:
  int level;
};

int Endangered::critical = 1;

class Bear : public virtual ZooAnimal {
 public:
  Bear(std::string name, bool on_exhibit, std::string species)
      : ZooAnimal(), name(name), on_exhibit(on_exhibit), species(species) {}
  std::string name;

 private:
  bool on_exhibit;
  std::string species;
};

class Raccoon : public virtual ZooAnimal {
  // ...
};
// multi-inheritance
class Panda : public Bear, public Raccoon, public Endangered {
 public:
  Panda(std::string name, bool on_exhibit, std::string species)
      : ZooAnimal(),
        Bear(name, on_exhibit, species),
        Raccoon(),
        Endangered(Endangered::critical) {}
  virtual void print() {
    // 这里指明Bear::name，避免ambiguity
    std::cout << Bear::name << std::endl;
  }
};

// 多重继承构造函数
struct Base1 {
  Base1() = default;
  Base1(const std::string &);
  Base1(std::shared_ptr<int>);
  virtual ~Base1() {}
};

struct Base2 {
  Base2() = default;
  Base2(const std::string &);
  Base2(std::shared_ptr<int>);
  virtual ~Base2();
};

struct D1 : public Base1, public Base2 {
  using Base1::Base1;
  using Base2::Base2;

  // 由于Base1和Base2构造函数相同，必须定义D1自己的构造函数
  D1(const std::string &s) : Base1(s), Base2(s) {}

  // 由于定义了D1自己的构造函数，则必须出现默认构造函数
  D1() = default;
};
