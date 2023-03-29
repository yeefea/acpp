#pragma once
#include <string>
class HasPtrLikeValue
{

public:
  HasPtrLikeValue(const std::string &s = std::string()) : ps(new std::string(s)) {}
  HasPtrLikeValue(const HasPtrLikeValue &p) : ps(new std::string(*p.ps)) {} // 1 拷贝构造
  HasPtrLikeValue &operator=(const HasPtrLikeValue &rhs)                    // 2 拷贝赋值
  {
    delete ps;
    ps = new std::string(*rhs.ps);
    return *this;
  }
  ~HasPtrLikeValue() { delete ps; }              // 3 析构
  HasPtrLikeValue(HasPtrLikeValue &&p) noexcept {}        // 4 移动构造
  HasPtrLikeValue &operator=(const HasPtrLikeValue &&rhs) // 5 移动赋值
  {
    delete ps;
    ps = new std::string(*rhs.ps);
    return *this;
  }

  std::string *ps = nullptr;
};

struct NoCopy
{

  NoCopy() = default;
  NoCopy(const NoCopy &) = delete;
  NoCopy &operator=(const NoCopy &) = delete;

private:
  int field1;
};