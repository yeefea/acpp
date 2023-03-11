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