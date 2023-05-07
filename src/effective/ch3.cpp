
#include "ch3.h"

#include <cstdlib>
#include <cstring>
#include "utils.h"

Str::Str(const char *value)
{
  if (value)
  {
    data = new char[strlen(value) + 1];
    strcpy(data, value);
    data[strlen(value)] = '\0';
  }
  else
  {
    data = new char[1];
    *data = '\0';
  }
}

Str::Str(const Str &rhs)
{
  data = new char[strlen(rhs.data) + 1];
  strcpy(data, rhs.data);
  data[strlen(rhs.data)] = '\0';
}

Str &Str::operator=(const Str &rhs)
{
  delete[] data; // release existing memory
  data = new char[strlen(rhs.data) + 1];
  strcpy(data, rhs.data);
  data[strlen(rhs.data)] = '\0';
  return *this;
}

inline Str::~Str()
{
  delete[] data;
}

void demo_dynamic_memory()
{
}

void demo_initialization_order()
{
  // 条款 13: 初始化列表中成员列出的顺序和它们在类中声明的顺序相同
  // 对一个对象的所有成员来说，它们的析构函数被调用的顺序总是和它们在构造函数里被创建的顺序相反
  array<int> arr1(0, 9);
  array<int> arr2(1, 10);
  // 构造顺序 arr1->arr2
  // 析构顺序 arr2->arr1
  // 基本的一条是：如果想弄清楚对象被初始化时到底是怎么做的，请确信你的初始化列表中成员列出的顺序和成员在类内声明的顺序一致。
}

class DerivedAwov : public Awov
{
};

void demo_abstract_base()
{
  // Awov a;  error
  DerivedAwov d; // ok
}

int main()
{
  RUN_DEMO(demo_dynamic_memory);
  RUN_DEMO(demo_initialization_order);

  return EXIT_SUCCESS;
}