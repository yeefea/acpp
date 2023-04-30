#pragma once
#include <iostream>
#include <vector>

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

template <typename It>
void describe_container(It beg, It end)
{
  std::cout << "[";
  size_t size = 0;
  auto iter = beg;
  if (iter != end)
  {
    std::cout << *iter;
    ++iter;
    ++size;
  }
  for (; iter != end; ++iter)
  {
    std::cout << ", " << *iter;
    ++size;
  }
  std::cout << "] size: " << size << std::endl;
}

template <typename It>
void describe_maplike(It beg, It end)
{
  std::cout << '{' << std::endl;
  for (; beg != end; ++beg)
  {
    std::cout << "  ";
    describe_pair(*beg);
  }
  std::cout << '}' << std::endl;
}

// deprecated use describe_container
template <typename It>
void describe_sequential_container(It beg, It end)
{
  std::cout << "[";
  size_t size = 0;
  auto iter = beg;
  if (iter != end)
  {
    std::cout << *iter;
    ++iter;
    ++size;
  }
  for (; iter != end; ++iter)
  {
    std::cout << ", " << *iter;
    ++size;
  }
  std::cout << "] size: " << size << std::endl;
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

#define LOG(X) std::cout << OUTPUT_VAL(X) << std::endl;

#define LOG_VEC(X)         \
  do                       \
  {                        \
    std::cout << #X " = "; \
    describe_vector(X);    \
  } while (0)

extern const int bufsize;
extern const double pi;

#define YEEFEA_NS_OPEN \
  namespace yeefea     \
  {
#define YEEFEA_NS_CLOSE } // namespace yeefea
