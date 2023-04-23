#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

#include "utils.h"

void demo_algo() {
  // find in vector
  std::vector<int> ivec = {1, 2, 3, 4, 5, 6, 6, 7, 32};

  auto it = std::find(ivec.cbegin(), ivec.cend(), 42);

  bool found = it != ivec.cend();
  LOG(found);  // false
  it = std::find(ivec.cbegin(), ivec.cend(), 32);

  found = it != ivec.cend();
  LOG(found);  // true

  // find in array
  int ia[] = {2423, 232312, 12312, 1111, 149, 32};
  auto pi = std::find(std::begin(ia), std::end(ia), 32);
  found = pi != std::end(ia);
  LOG(found);

  // count in vector
  auto cnt = std::count(ivec.cbegin(), ivec.cend(), 6);
  LOG(cnt);
}

void demo_readonly_algo() {
  std::vector<double> dvec1 = {1.0, 2.0, 3.0, 4.4, 5.6};
  // acc
  int sum = std::accumulate(dvec1.cbegin(), dvec1.cend(), 0.0);
  LOG(sum);

  std::vector<std::string> svec = {"abc", "efg", "xyz"};
  // 注意下面最后一个参数只能用string，不能用字面值，因为const
  // char*没有operator+
  std::string initstr = "<prefix>";
  auto jstr = std::accumulate(svec.cbegin(), svec.cend(), initstr);
  LOG(initstr);
  LOG(jstr);

  // equal
  decltype(dvec1) dvec2 = {1.0, 2.0, 3.0, 4.4};
  // 短的vector放前面
  bool eq = std::equal(dvec2.cbegin(), dvec2.cbegin(), dvec1.cbegin());
  LOG(eq);
}

void demo_modify_algo() {
  std::vector<double> dvec1(10, 123.0);
  describe_sequential_container(dvec1.cbegin(), dvec1.cend());

  // fill
  std::fill(dvec1.begin(), dvec1.begin() + dvec1.size() / 2, 0.01);
  describe_sequential_container(dvec1.cbegin(), dvec1.cend());

  // fill_n
  std::fill_n(dvec1.begin() + dvec1.size() / 2, 3, 0.03);
  describe_sequential_container(dvec1.cbegin(), dvec1.cend());
}

void demo_back_inserter() {
  std::vector<int> ivec1;
  describe_vector(ivec1);

  // back_inserter, 类似于append操作
  auto it = std::back_inserter(ivec1);

  for (int i = 100; i < 110; ++i) {
    *it = i;  // append i
  }

  *it = 123;  // append 123
  describe_vector(ivec1);

  // fill_n + back_inserter
  std::fill_n(std::back_inserter(ivec1), 10, 0);  // append 0 0 0 0 0 0 0 0 0 0
  describe_vector(ivec1);
}
void demo_copy() {
  int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  decltype(a1) a2;

  describe_array(std::begin(a1), std::end(a1));
  describe_array(std::begin(a2), std::end(a2));

  // copy a1 -> a2
  auto ret = std::copy(std::begin(a1), std::end(a1), a2);
  describe_array(std::begin(a2), std::end(a2));

  // copy + back_inserter
  std::vector<int> ivec;
  std::copy(std::cbegin(a1), std::cend(a1), std::back_inserter(ivec));
  describe_vector(ivec);
}

void demo_replace() {
  int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  describe_array(std::begin(a1), std::end(a1));

  // 4 -> 42
  std::replace(std::begin(a1), std::end(a1), 4, 42);
  describe_array(std::begin(a1), std::end(a1));
}

void demo_rearrange() {
  std::vector<std::string> svec = {"a",     "fox", "red", "quick",
                                   "jumps", "a",   "hill"};
  describe_vector(svec);
  // unique先要sort
  std::sort(svec.begin(), svec.end());
  describe_vector(svec);
  // unique
  auto end_unique = std::unique(svec.begin(), svec.end());
  describe_vector(svec);
  // 删掉[end_unique, end)区间内的元素
  svec.erase(end_unique, svec.end());
  describe_vector(svec);
}

void demo_lambda() {
  auto shorter = [](const std::string &a, const std::string &b) -> bool {
    return a.size() < b.size();
  };
  
  std::vector<std::string> svec = {"a",     "fox", "red", "quick",
                                   "jumps", "a",   "hill"};
  describe_vector(svec);
  std::stable_sort(svec.begin(), svec.end(), shorter);
  describe_vector(svec);
}
void demo_() {}
int main(int argc, char **argv) {
  RUN_DEMO(demo_algo);
  RUN_DEMO(demo_readonly_algo);
  RUN_DEMO(demo_modify_algo);
  RUN_DEMO(demo_back_inserter);
  RUN_DEMO(demo_copy);
  RUN_DEMO(demo_replace);
  RUN_DEMO(demo_rearrange);
  RUN_DEMO(demo_lambda);
  RUN_DEMO(demo_);
}