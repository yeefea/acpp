#pragma once

#include <vector>
#include <memory>
#include <initializer_list>
#include <stdexcept>

template <typename T>
class Blob
{
public:
  typedef typename std::vector<T>::size_type size_type;

  Blob();
  Blob(std::initializer_list<T> il);
  size_type size() const { return data->size(); }
  bool empty() const { return data->empty(); }
  void push_back(const T &t) { data->push_back(t); }
  void pop_back();

  T &front();
  T &back();

private:
  std::shared_ptr<std::vector<T>> data;
  void check(size_type i, const std::string &msg) const;
};

template <typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<std::string>>()) {}

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<std::string>>(il)) {}

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
  if (i >= data->size())
  {
    throw std::out_of_range(msg);
  }
}

template <typename T>
T &Blob<T>::front()
{
  check(0, "front on empty blob");
  return data->front();
}

template <typename T>
T &Blob<T>::back()
{
  check(0, "back on empty blob");
  return data->back();
}

template <typename T>
void Blob<T>::pop_back()
{
  check(0, "pop_back on empty blob");
  return data->pop_back();
}
