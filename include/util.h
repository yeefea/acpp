#ifndef GUARD_util_h
#define GUARD_util_h
#include <string>
#include <vector>
/*
Deprecated!

*/
void describe_string_vector(const std::vector<std::string> &);
void describe_int_vector(const std::vector<int> &);

template <typename T>
inline void describe_vector(const std::vector<T> &vec) {
  std::cout << "[ ";
  for (auto iter = vec.begin(); iter != vec.end();) {
    std::cout << *iter;
    ++iter;
    if (iter != vec.end()) {
      std::cout << ",";
    }
    std::cout << " ";
  }
  std::cout << "] size: " << vec.size() << std::endl;
}

#endif