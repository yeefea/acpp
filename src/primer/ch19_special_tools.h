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

union ComplexToken {
  // union成员默认public，这点和struct一样
  std::string sval;
  char cval;
  int ival;
  double dval;

  // union如果有类类型成员，则无法合成构造、析构函数，要手工定义
  ComplexToken() : ival(1) {}
  ~ComplexToken() {}
};

// union的管理类，discriminant
class ComplexToken2 {
 public:
  ComplexToken2() : tok(INT), ival{0} {}
  ComplexToken2(const ComplexToken2& t) : tok(t.tok) { copy_union(t); }
  ComplexToken2& operator=(const ComplexToken2& t);
  ~ComplexToken2() {
    if (tok == STR) {
      sval.~basic_string();
    }
  }

  ComplexToken2& operator=(const std::string&);
  ComplexToken2& operator=(char);
  ComplexToken2& operator=(int);
  ComplexToken2& operator=(double);

 private:
  // enum元素和union成员一一对应
  enum { INT, CHAR, DBL, STR } tok;
  union {
    char cval;
    int ival;
    double dval;
    std::string sval;
  };
  void copy_union(const ComplexToken2&);
};

// copy constructor
ComplexToken2& ComplexToken2::operator=(const ComplexToken2& t) {
  if (tok == STR && t.tok != STR) {
    sval.~basic_string();  // 析构
  }
  // 左边的str已经析构函数掉了

  if (tok == STR && t.tok == STR) {
    // 两边都是string，直接赋值
    sval = t.sval;
  } else {
    copy_union(t);
  }
  tok = t.tok;
  return *this;
}

ComplexToken2& ComplexToken2::operator=(const std::string& s) {
  if (tok == STR) {
    sval = s;
  } else {
    new (&sval) std::string(s);
  }
  tok = STR;
  return *this;
}

ComplexToken2& ComplexToken2::operator=(char c) {
  if (tok == STR) {
    sval.~basic_string();
  }
  cval = c;
  tok = CHAR;
  return *this;
}

ComplexToken2& ComplexToken2::operator=(int i) {
  if (tok == STR) {
    sval.~basic_string();
  }
  ival = i;
  tok = INT;
  return *this;
}

ComplexToken2& ComplexToken2::operator=(double d) {
  if (tok == STR) {
    sval.~basic_string();
  }
  dval = d;
  tok = DBL;
  return *this;
}

void ComplexToken2::copy_union(const ComplexToken2& t) {
  switch (t.tok) {
    case ComplexToken2::INT:
      ival = t.ival;
      break;
    case ComplexToken2::CHAR:
      cval = t.cval;
      break;
    case ComplexToken2::DBL:
      dval = t.dval;
      break;
    case ComplexToken2::STR:
      new (&sval) std::string(t.sval);  // placement new operator
      break;
  }
}

typedef unsigned int Bit;

class File {
 public:
  Bit mode : 2;        // 2 bits
  Bit modified : 1;    // 1 bit
  Bit prot_owner : 3;  // 3 bits
  Bit prot_group : 3;  // 3 bits
  Bit prot_world : 3;  // 3 bits

  enum modes { READ = 01, WRITE = 02, EXECUTE = 03 };
  File() : prot_owner(7), prot_group(5), prot_world(5) {}
  File& open(modes);
  void close();
  void write();
  bool is_read() const { return mode & READ; }
  void set_write() { mode |= WRITE; }
};

void File::write() {
  modified = 1;
  std::cout << "write file" << std::endl;
}

void File::close() {
  if (modified) {
    std::cout << "write to disk" << std::endl;
  }
  std::cout << "close file" << std::endl;
}

File& File::open(modes m) {
  mode |= READ;
  std::cout << "open file" << std::endl;
  if (m & WRITE) {
    std::cout << "open file in write mode" << std::endl;
  }
  return *this;
}

class VObj {
 public:
  // 必须自定义volatile的拷贝构造函数
  VObj(const volatile VObj&);
  VObj& operator=(const volatile VObj&);
  VObj& operator=(const volatile VObj&) volatile;
};