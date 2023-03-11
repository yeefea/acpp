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

#define RUN_DEMO(X)                      \
  do                                     \
  {                                      \
    std::cout << ">>> " #X << std::endl; \
    X();                                 \
    std::cout << std::endl;              \
  } while (0)

#define OUTPUT_VAL(X) #X "=" << (X)

extern const int bufsize;
extern const double pi;

#define YEEFEA_NS_OPEN \
  namespace yeefea     \
  {

#define YEEFEA_NS_CLOSE } // namespace yeefea
