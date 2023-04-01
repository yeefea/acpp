#pragma once

#include <string>
#include <iostream>
#include "utils.h"

class HasPtrLikeValue;
inline void swap(HasPtrLikeValue &lhs, HasPtrLikeValue &rhs);

class HasPtrLikeValue
{
  friend void swap(HasPtrLikeValue &, HasPtrLikeValue &);

public:
  HasPtrLikeValue(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}
  HasPtrLikeValue(const HasPtrLikeValue &p) : ps(new std::string(*p.ps)), i(p.i) {}
  HasPtrLikeValue &operator=(const HasPtrLikeValue &rhs)
  {
    // 赋值运算符
    // 2个关键点
    // 1. 要可以给自身赋值，解决办法是销毁左侧对象前拷贝右侧对象
    // 2. 大多时候组合了析构函数和拷贝构造函数
    auto newp = new std::string(*rhs.ps); // 拷贝
    delete ps;                            // 释放内存
    ps = newp;
    i = rhs.i;
    return *this;
  }
  // copy and swap写法
  // swap版本的赋值运算符参数一般不是引用
  // HasPtrLikeValue &operator=(HasPtrLikeValue rhs)
  // {
  //   swap(*this, rhs);
  //   return *this;
  // }

  ~HasPtrLikeValue() { delete ps; }

private:
  std::string *ps;
  int i;
};

// swap是用于优化代码，避免不必要的拷贝
inline void swap(HasPtrLikeValue &lhs, HasPtrLikeValue &rhs)
{
  std::cout << "swap HasPtrLikeValue: " << *lhs.ps << "<=>" << *rhs.ps << std::endl;
  using std::swap; // 注意一定要using
  swap(lhs.ps, rhs.ps);
  swap(lhs.i, rhs.i);
}

class HasPtrLikePtr
{
public:
  HasPtrLikePtr(const std::string &s = std::string())
      : ps(new std::string(s)), i(0), use(new std::size_t(1)) {}
  HasPtrLikePtr(const HasPtrLikePtr &p) // copy
      : ps(p.ps), i(p.i), use(p.use)
  {
    ++*use;
  }
  HasPtrLikePtr &operator=(const HasPtrLikePtr &rhs); // assign
  ~HasPtrLikePtr();
  const std::size_t refcnt() const
  {
    return *use;
  }

private:
  std::string *ps;
  int i;
  std::size_t *use; // ref count
};

HasPtrLikePtr::~HasPtrLikePtr()
{

  if (--*use == 0)
  {
    delete ps;
    delete use;
    std::cout << OUTPUT_VAL(refcnt()) << std::endl;
    std::cout << "HasPtrLikePtr: memory released" << std::endl;
  }
  else
  {
    std::cout << OUTPUT_VAL(refcnt()) << std::endl;
  }
}

HasPtrLikePtr &HasPtrLikePtr::operator=(const HasPtrLikePtr &rhs)
{
  ++*rhs.use;
  if (--*use == 0)
  {
    delete ps;
    delete use;
  }
  // copy rhs
  ps = rhs.ps;
  i = rhs.i;
  use = rhs.use;
  return *this;
}