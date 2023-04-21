#include <gtest/gtest.h>

#include <iostream>
#include <vector>

TEST(demo_test, demo_test_vector) {
  std::vector<int> ivec = {1, 2, 3, 4, 5};
  ASSERT_EQ(ivec.size(), 5);
  // std::cout << "hello gtest" << std::endl;
  // std::cout << std::endl;
}