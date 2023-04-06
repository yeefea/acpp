#pragma once

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "utils.h"

// 模板声明
template <typename>
class BlobPtr;  // 前置声明，Blob中声明友元需要

template <typename>
class Blob;  // 前置声明，operator==需要

template <typename T>
bool operator==(const Blob<T> &, const Blob<T> &);  // 运算符声明，前置声明

class AllFriend {};
template <typename T>
class Blob {
  // 1. 类模板包含非模板友元，则友元可以访问所有模板实例
  friend class AllFriend;

  // 2.
  // 一对一友好关系，友元关系限定在相同的类型之间，需要先声明模板，再把模板形参T做实参
  friend class BlobPtr<T>;
  friend bool operator==(const Blob<T> &, const Blob<T> &);  // 和上面相同

 public:
  typedef T value_type;
  typedef typename std::vector<T>::size_type size_type;

  Blob();
  Blob(std::initializer_list<T> il);
  size_type size() const { return data->size(); }
  bool empty() const { return data->empty(); }
  void push_back(const T &t) { data->push_back(t); }
  void push_back(T &&t) { data->push_back(std::move(t)); }
  void pop_back();

  T &front();
  T &back();
  T &operator[](size_type i);

  void describe(std::ostream &os) { describe_vector(*data); }

 private:
  std::shared_ptr<std::vector<T>> data;
  void check(size_type i, const std::string &msg) const;
};

// 在类外定义成员，很繁琐
// constructor
template <typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()) {}

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il)
    : data(std::make_shared<std::vector<T>>(il)) {}

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const {
  if (i >= data->size()) {
    throw std::out_of_range(msg);
  }
}

template <typename T>
T &Blob<T>::front() {
  check(0, "front on empty blob");
  return data->front();
}

template <typename T>
T &Blob<T>::back() {
  check(0, "back on empty blob");
  return data->back();
}

template <typename T>
void Blob<T>::pop_back() {
  check(0, "pop_back on empty blob");
  return data->pop_back();
}

template <typename T>
T &Blob<T>::operator[](size_type i) {
  check(i, "subscript out of range");
  return (*data)[i];  // 注意，不能写data[i]
}

// 前置声明，特定实例的友元需要
template <typename T>
class Pal;

class C {
  // 3. 声明模板的一个实例作为友元
  friend class Pal<C>;
  // 4. 声明模板的所有实例都是友元
  template <typename T>
  friend class Pal2;  // 不需要前置声明
};

template <typename T>
class C2 {
  // 具有相同类型参数T的模板实例作为友元
  friend class Pal<T>;  // 需要前置声明
  template <typename X>
  friend class Pal2;  // 不需要前置声明，类型参数必须与T不同，这里是X
  friend class Pal3;  // 不需要前置声明
};

template <typename T>
class Pal2 {};

template <typename T>
class Bar {
  // 5. 实例化Bar的类型参数T作为友元，例如Foo是Bar<Foo>的友元
  friend T;
};
