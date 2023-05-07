#pragma once

#include <vector>
#include <cstdint>
#include <iostream>

class Str
{
public:
  Str(const char *value);
  Str(const Str &);
  Str &operator=(const Str &);
  ~Str();

private:
  char *data;
};

template <typename T>
class array
{
public:
  array(int lowbound, int highbound);
  ~array();

private:
  // std::vector<T> data; // 错 必须放在size后面
  size_t size;
  int lbound, hbound;
  std::vector<T> data; // 必须放在size后面
};

template <typename T>
array<T>::array(int lowbound, int highbound)
    : size(highbound - lowbound + 1), lbound(lowbound), hbound(highbound), data(size)
{
  std::cout << "construct array[" << lowbound << ", " << highbound << "]" << std::endl;
}

template <typename T>
array<T>::~array()
{
  std::cout << "destruct array[" << lbound << ", " << hbound << "]" << std::endl;
}

class Awov
{
public:
  Awov() {}

  virtual ~Awov() = 0;
};

// 不要忘记定义基类的纯虚析构函数
Awov::~Awov() {}