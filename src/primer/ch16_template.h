#pragma once
#include <cstring>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <functional>

template <typename T> // 模板参数列表
int compare(const T &v1, const T &v2)
{
  if (std::less<T>()(v1, v2)) // v1<v2
  {
    return -1;
  }
  if (std::less<T>(v2, v1)) // v2<v1
  {
    return 1;
  }
  return 0;
}

// inline和constexpr都放在template后面
template <typename T>
inline T add(const T v1, const T v2)
{
  return v1 + v2;
}

// 非类型模板参数，可以是整型、指向对象或函数的指针或左值引用，必须是constexpr
template <unsigned N, unsigned M>
int compare_arr(const char (&p1)[N], const char (&p2)[M])
{
  return strcmp(p1, p2);
}

template <typename T>
constexpr int play_constexpr_template(T v)
{
  return 123;
}

// class template

template <typename T>
class Blob
{

public:
  typedef typename std::vector<T>::size_type size_type;

private:
  std::shared_ptr<std::vector<T>> data;
  void check(size_type i, const std::string &mgs) const;
};

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{

  if (i >= data->size())
  {
    throw std::out_of_range(msg);
  }
}