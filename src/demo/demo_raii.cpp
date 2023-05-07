#include <iostream>
#include "demo_raii.h"

G::G()
{
  std::cout << "START" << std::endl;
}
G::~G()
{
  std::cout << "EXIT" << std::endl;
}

// G _g; // global scope

int main()
{
  std::cout << "main" << std::endl;
  return 0;
}