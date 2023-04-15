#include <bitset>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <random>
#include <regex>
#include <tuple>
#include <vector>

#include "utils.h"

void demo_tuple() {
  std::tuple<std::size_t, std::size_t, std::size_t> p1;

  auto x = std::get<0>(p1);
  auto y = std::get<1>(p1);
  auto z = std::get<2>(p1);

  std::cout << OUTPUT_VAL(x) << ", " << OUTPUT_VAL(y) << ", " << OUTPUT_VAL(z)
            << std::endl;

  decltype(p1) p2 = std::make_tuple(1, 2, 3);

  x = std::get<0>(p2);
  y = std::get<1>(p2);
  z = std::get<2>(p2);

  std::cout << OUTPUT_VAL(x) << ", " << OUTPUT_VAL(y) << ", " << OUTPUT_VAL(z)
            << std::endl;

  std::get<2>(p2) = 555;  // write

  x = std::get<0>(p2);
  y = std::get<1>(p2);
  z = std::get<2>(p2);
  std::cout << OUTPUT_VAL(x) << ", " << OUTPUT_VAL(y) << ", " << OUTPUT_VAL(z)
            << std::endl;

  auto sz = std::tuple_size<decltype(p1)>::value;
  std::cout << OUTPUT_VAL(sz) << std::endl;

  // 第一个元素的类型std::tuple_element<1, decltype(p1)>::type
  std::tuple_element<1, decltype(p1)>::type yy = std::get<1>(p1);

  std::cout << OUTPUT_VAL(yy) << std::endl;

  std::tuple<std::size_t, std::size_t> p3;

  bool less = p1 < p2;
  std::cout << std::boolalpha;
  std::cout << OUTPUT_VAL(less) << std::endl;

  // less = p1 < p3;  这样不能编译，成员数量不同，不能比较
}

void demo_bitset() {
  std::bitset<32> bitvec(1U);

  std::cout << OUTPUT_VAL(bitvec) << std::endl;

  std::bitset<13> bitvec1(0xbeef);  // 高位被丢弃
  std::bitset<20> bitvec2(0xbeef);
  std::bitset<80> bitvec3(~0ULL);  // 高位补0

  std::bitset<32> bitvec4("1100");

  std::string bits("11111111000000000011001101");
  std::bitset<32> bitvec5(bits, 5, 4);
  std::bitset<32> bitvec6(bits, bits.size() - 4);

  std::cout << OUTPUT_VAL(bitvec1) << std::endl;
  std::cout << OUTPUT_VAL(bitvec2) << std::endl;
  std::cout << OUTPUT_VAL(bitvec3) << std::endl;
  std::cout << OUTPUT_VAL(bitvec4) << std::endl;
  std::cout << OUTPUT_VAL(bitvec5) << std::endl;
  std::cout << OUTPUT_VAL(bitvec6) << std::endl;
  bitvec6.flip();
  std::cout << OUTPUT_VAL(bitvec6) << std::endl;
  std::cout << OUTPUT_VAL(bitvec6.to_string('a', 'b')) << std::endl;
}

void demo_regex() { std::string pattern("[^c]ei"); }

void demo_random() {
  std::default_random_engine e;

  for (std::size_t i = 0; i < 10; ++i) {
    std::cout << e() << " ";
  }
  std::cout << std::endl;

  std::normal_distribution<> n(4, 1.5);

  std::vector<unsigned> vals(9);

  for (size_t i = 0; i != 200; ++i) {
    unsigned v = lround(n(e));
    if (v < vals.size()) {
      ++vals[v];
    }
  }
  for (size_t j = 0; j != vals.size(); ++j) {
    std::cout << j << ": " << std::string(vals[j], '*') << std::endl;
  }
}

void demo_io(){

}
int main(int argc, char **argv) {
  RUN_DEMO(demo_tuple);
  RUN_DEMO(demo_bitset);
  RUN_DEMO(demo_regex);
  RUN_DEMO(demo_random);
  RUN_DEMO(demo_io);
  return EXIT_SUCCESS;
}