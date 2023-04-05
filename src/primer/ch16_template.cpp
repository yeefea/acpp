#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <memory>
#include <vector>

#include "ch16_template.h"
#include "utils.h"
#include "blob.h"

void demo_function_template()
{

  auto cmp_res = compare(1, 2);
  std::cout << OUTPUT_VAL(cmp_res) << std::endl;

  cmp_res = compare<double>(3.0, 1);
  std::cout << OUTPUT_VAL(cmp_res) << std::endl;

  cmp_res = compare<char>('a', 'a');
  std::cout << OUTPUT_VAL(cmp_res) << std::endl;

  cmp_res = compare_arr("hello", "world");
  std::cout << OUTPUT_VAL(cmp_res) << std::endl;

  auto res = play_constexpr_template(1);
  std::cout << OUTPUT_VAL(res) << std::endl;
}

void demo_class_template()
{
  Blob<int> ia;
  ia.describe(std::cout);
  Blob<int> ia2 = {0, 1, 2, 3, 4, 5};
  ia2.describe(std::cout);

  auto ifront = ia2.front();
  auto iback = ia2.back();

  std::cout << OUTPUT_VAL(ifront) << ", " << OUTPUT_VAL(iback) << std::endl;
}

void demo_template()
{
  std::shared_ptr<std::vector<std::string>> pvs = std::make_shared<std::vector<std::string>>();
  pvs->push_back("123123");
  pvs->push_back("1231233333");
  describe_vector(*pvs);
}

int main(int argc, char **argv)
{
  RUN_DEMO(demo_function_template);
  RUN_DEMO(demo_class_template);
  RUN_DEMO(demo_template);
  return EXIT_SUCCESS;
}