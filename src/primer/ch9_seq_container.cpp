#include <array>
#include <cstdint>
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

  std::vector<int> ivec2{10};
  std::vector<std::string> svec2{10};

  describe_sequential_container(ivec2.begin(), ivec2.end());
  describe_sequential_container(svec2.begin(), svec2.end());

  LOG(svec[0]);

  describe_vector(svec);
}

void demo_deque() {
  std::deque<int> q = {1, 2, 3, 4, 5};

  q.push_back(6);
  q.push_front(0);

  describe_sequential_container(q.begin(), q.end());
}

void demo_list() {
  std::list<std::string> sl = {"111", "222", "333"};
  describe_sequential_container(sl.begin(), sl.end());
}

int main(int argc, char **argv) {
  RUN_DEMO(demo_vector);
  RUN_DEMO(demo_deque);
  RUN_DEMO(demo_list);
}