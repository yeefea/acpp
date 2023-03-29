#pragma once
#include <vector>
#include <iostream>

template <typename T>
void describe_vector(const std::vector<T> &vec)
{
  std::cout << "[";
  auto iter = vec.begin();
  if (iter != vec.end())
  {
    std::cout << *iter;
    ++iter;
  }
  for (; iter != vec.end(); ++iter)
  {
    std::cout << ", " << *iter;
  }
  std::cout << "] size: " << vec.size() << std::endl;
}

template <typename T>
void describe_array(const T *begin, const T *end)
{
  std::cout << "[";
  auto iter = begin;
  if (iter != end)
  {
    std::cout << *iter;
    ++iter;
  }
  for (; iter != end; ++iter)
  {
    std::cout << ", " << *iter;
  }
  std::cout << "] size: " << (end - begin) << std::endl;
}

template <typename T>
std::ostream &serialize_arr(std::ostream &os, const T *begin, const T *end)
{
  os << "[";
  auto iter = begin;
  if (iter != end)
  {
    os << *iter;
    ++iter;
  }
  for (; iter != end; ++iter)
  {
    os << ", " << *iter;
  }
  os << "]";
  return os;
}

#define RUN_DEMO(X)                      \
  do                                     \
  {                                      \
    std::cout << ">>> " #X << std::endl; \
    X();                                 \
    std::cout << "\n\n";                 \
  } while (0)

#define SKIP_RUN_DEMO(X)

#define OUTPUT_VAL(X) #X "=" << (X)
#define OUTPUT_MEMBER(OBJ, M) #M "=" << (OBJ.M)

extern const int bufsize;
extern const double pi;

#define YEEFEA_NS_OPEN \
  namespace yeefea     \
  {

#define YEEFEA_NS_CLOSE } // namespace yeefea
