#include <gtest/gtest.h>

int square(int i) { return i * i; }

TEST(test_std, test_string) {
  // assert real, expected

  ASSERT_EQ(square(1), 1);
  ASSERT_EQ(square(2), 4);
  ASSERT_EQ(square(3), 9);
  ASSERT_EQ(square(4), 16);

  ASSERT_EQ(1, 1);
}
