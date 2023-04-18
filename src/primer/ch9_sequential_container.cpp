#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <string>
#include <vector>

#include "utils.h"

void demo_vector() {
  // ch3
  std::vector<int> ivec;
  std::vector<std::vector<std::string>> file;
  std::vector<std::string> svec(10, "sss");

  // std::vector<int&> ref_vec; 不行，没有引用的vector，引用不是对象

  LOG(svec[0]);

  describe_vector(svec);
}

void demo_deque() {}

int main(int argc, char **argv) {
  RUN_DEMO(demo_vector);
  RUN_DEMO(demo_deque);
}