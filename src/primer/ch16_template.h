#pragma once
#include <cstring>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

#include "utils.h"

template <typename T>  // 模板参数列表
int compare(const T &v1, const T &v2) {
  // if (std::less<T>()(v1, v2)) // v1<v2
  // {
  //   return -1;
  // }
  // if (std::less<T>(v2, v1)) // v2<v1
  // {
  //   return 1;
  // }
  if (v1 < v2) {
    return -1;
  }
  if (v2 < v1) {
    return 1;
  }
  return 0;
}

// 模板默认参数
template <typename T, typename F = std::less<T>>
int general_compare(const T &v1, const T &v2, F f = F()) {
  if (f(v1, v2)) {
    return -1;
  }
  if (f(v2, v2)) {
    return 1;
  }
  return 0;
}

// inline和constexpr都放在template后面
template <typename T>
inline T add(const T v1, const T v2) {
  return v1 + v2;
}

// 非类型模板参数，可以是整型、指向对象或函数的指针或左值引用，必须是constexpr
template <unsigned N, unsigned M>
int compare_arr(const char (&p1)[N], const char (&p2)[M]) {
  return strcmp(p1, p2);
}

template <typename T>
constexpr int play_constexpr_template(T v) {
  return 123;
}

// 类模板总是需要 <>，即使有默认参数

template <typename T = int>
class Numbers {
 public:
  Numbers(T v) : val(v) {}

 private:
  T val;
};

// 普通类的成员模板
class DebugDelete {
 public:
  DebugDelete(std::ostream &s = std::cerr) : os(s) {}

  template <typename T>
  void operator()(T *p) const {
    os << "deleting unique_ptr" << std::endl;
    delete p;
  }

 private:
  std::ostream &os;
};

// 类模板的成员模板

template <typename T>
class Blob2 {
 public:
  template <typename It>
  Blob2(It b, It e) : data(std::make_shared<std::vector<T>>(b, e)) {
    describe_vector(*data);
    std::cout << std::endl;
  }

 private:
  std::shared_ptr<std::vector<T>> data;
};

template <typename It>
auto fcn(It beg, It end) -> decltype(*beg) {
  return *beg;
}

template <typename It>
auto fcn2(It beg, It end) ->
    typename std::remove_reference<decltype(*beg)>::type {
  // 返回的不是左值引用，而是拷贝
  return *beg;
}
