#include <cstdlib>
#include <cstddef>

#include "ch16_template.h"
#include "utils.h"

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

void demo_class_template(){

}

int main(int argc, char **argv)
{
  RUN_DEMO(demo_function_template);
  RUN_DEMO(demo_class_template);
  return EXIT_SUCCESS;
}