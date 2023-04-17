#pragma once
#include <cstdlib>
#include <functional>
#include <iostream>
#include <new>
#include <stdexcept>

void* operator new(size_t size) {
  if (void* mem = malloc(size)) {
    std::cout << "alloc " << size << " bytes at " << mem << std::endl;
    return mem;
  }
  throw std::runtime_error("bad_alloc");
}

void* operator new[](size_t size) {
  if (void* mem = malloc(size)) {
    std::cout << "alloc array " << size << " bytes at " << mem << std::endl;
    return mem;
  }
  throw std::runtime_error("bad_alloc");
}

void operator delete(void* ptr) noexcept {
  std::cout << "release " << ptr << std::endl;
  free(ptr);
}
void operator delete[](void* ptr) noexcept {
  std::cout << "release array " << ptr << std::endl;
  free(ptr);
}

// void* operator new(size_t size, std::nothrow_t& t) noexcept{

// }

class Base {
  friend bool operator==(const Base&, const Base&);

 public:
  void print(std::ostream& os) { os << "print Base" << std::endl; }
  virtual ~Base() {}
  virtual bool equal(const Base&) const { return true; }
};

class Derived : public Base {
 public:
  void print(std::ostream& os) { os << "print Derived" << std::endl; }
  bool equal(const Base& rhs) const {
    auto r = dynamic_cast<const Derived&>(rhs);
    return true;
  }
};

bool operator==(const Base& lhs, const Base& rhs) {
  return typeid(lhs) == typeid(rhs) && lhs.equal(rhs);
}

// scoped enumeration，一般都这样写
enum class open_modes { input, output, append };

// unscoped enumeration
enum color {
  red,
  yellow,
  green
};  // 枚举成员的scope和枚举类型color一样，都是全局的

// 错误，unscoped enum，color2重复定义了red, yellow, green
// enum color2 { red, yellow, green };

enum class peppers {
  red,
  yellow,
  green
};  // 这样是可以的，隐藏了外层的red,yellow,green

// anonymous enumeration
enum { floatPrec = 6, doublePrec = 10, doubleDoublePrec = 10 } e1, e2, e3;

// enum前置声明

// unscoped enum forward decl，必须指定类型
enum intValues : unsigned long long;

// scoped enum forward decl，
enum class intTypes;

// 默认enum从0开始，也可以自定义数值
enum class intTypes {
  charTyp = 8,
  shortTyp = 16,
  intTyp = 16,
  longTyp = 32,
  longLongTyp = 64
};

// 指定enum类型，unscopped没有默认类型，根据成员数量来确定，scopped默认int
enum intValues : unsigned long long {
  charTyp = 255,
  shortTyp = 65535,
  intTyp = 65535,
  // ...
  longLongType = 10000000000000ULL
};

class Screen {
 public:
  typedef std::string::size_type pos;
  using Action = Screen& (Screen::*)();
  enum Directions { HOME, FORWARD, BACK, UP, DOWN };

  Screen(std::string s) : contents(s) {}

  char get_cursor() const { return contents[cursor]; }

  char get() const { return 'a'; }
  char get(pos, pos) const { return 'a'; }

  Screen& move(Directions cm) { return (this->*Menu[cm])(); }

  Screen& home() { return *this; }
  Screen& forward() { return *this; }
  Screen& back() { return *this; }
  Screen& up() { return *this; }
  Screen& down() { return *this; }

  // data 返回成员变量指针的函数
  static const std::string Screen::*data() { return &Screen::contents; }

  std::string contents;
  pos cursor;
  pos height, width;

 private:
  static Action Menu[];
};

Screen::Action Screen::Menu[] = {
    &Screen::home, &Screen::forward, &Screen::back, &Screen::up, &Screen::down,
};

class Outer {
 public:
  int outer_m;
  class Inner;
};

class Outer::Inner {
 public:
  int inner_m;
  static int static_inner_m;
};

int Outer::Inner::static_inner_m = 1024;

union Token {
  char cval;
  int ival;
  double dval;
};