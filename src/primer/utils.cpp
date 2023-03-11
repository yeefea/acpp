#pragma once
#include "utils.h"

extern const double pi = 3.1416;
extern const int bufsize = 128;

template <>
void describe_vector(const std::vector<std::string> &vec)
{
  std::cout << "[";
  auto iter = vec.begin();
  if (iter != vec.end())
  {
    std::cout << "\"" << *iter << "\"";
    ++iter;
  }
  for (; iter != vec.end(); ++iter)
  {
    std::cout << ", \"" << *iter << "\"";
  }
  std::cout << "] size: " << vec.size() << std::endl;
}

template <>
void describe_array(const std::string *begin, const std::string *end)
{
  std::cout << "[";
  auto iter = begin;
  if (iter != end)
  {
    std::cout << "\"" << *iter << "\"";
    ++iter;
  }
  for (; iter != end; ++iter)
  {
    std::cout << ", \"" << *iter << "\"";
  }
  std::cout << "] size: " << (end - begin) << std::endl;
}

template <>
void describe_array(const char *begin, const char *end)
{
  std::cout << "[";
  auto iter = begin;
  if (iter != end)
  {
    std::cout << "\'" << *iter << "\'";
    ++iter;
  }
  for (; iter != end; ++iter)
  {
    std::cout << ", \'" << *iter << "\'";
  }
  std::cout << "] size: " << (end - begin) << std::endl;
}