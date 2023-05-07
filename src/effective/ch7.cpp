#include "ch7.h"

#include <iostream>

#include "utils.h"

void demo_tmp()
{
  constexpr int f = Factorial<10>::value;
  std::cout << f << std::endl;

  constexpr int res = Add<1, Factorial<10>::value>::value;
  std::cout << res << std::endl;
}

int main()
{

  RUN_DEMO(demo_tmp);

  return 0;
}