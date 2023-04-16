#include "ch18_tools.h"

#include <cstdlib>
#include <stdexcept>

#include "utils.h"

void ill_function() noexcept(false) {
  std::cout << "enter ill function" << std::endl;
  throw std::runtime_error("ill");
}

void good_function() noexcept {
  std::cout << "i will not throw" << std::endl;
  // throw std::runtime_error("123");
  // noexcept函数是可以throw的，编译器会报warning
  // 如果运行时throw了，程序直接panic
}

void demo_noexcept_deduction() noexcept(noexcept(good_function)) {
  std::cout << "noexcept(noexcept(good_function))=noexcept(true)" << std::endl;
}

void demo_exception() {
  try {
    ill_function();
  } catch (...) {
    std::cout << "catch all" << std::endl;
  }

  function_with_try_block();

  try {
    DemoConstructorObj<int> o = {1, 2, 3, 4};
  } catch (...) {
    std::cout << "construct o failed." << std::endl;
  }

  good_function();
}
int print(int i, int j, int k) { return i + j + k; }

void demo_namespace() {
  ::good_function();  // 全局命名空间
  A::C cobj;
  f(cobj);  // f能找到，因为参数是类C，会在类C所属的namespace A中查找
  // f2(); f2找不到
  A::f2();  // 一定要A::f2

  // 继承，命名空间查找
  BulkItem book1;
  display(book1);  // display定义在基类的namespace里，也被带进来了

  using namespace p1;  // 引入print(int)
  using namespace p2;     // 引入print(int, int), print(double, double)
  // 现在print有4个版本了
  print(1);
  print(1, 2);
  print(1, 2, 3);
  print(1.0, 2.0);
}

void demo_multi_inheritance() {}

void demo_virtual_inheritance() {}

int main(int argc, char** argv) {
  RUN_DEMO(demo_exception);
  RUN_DEMO(demo_namespace);
  RUN_DEMO(demo_multi_inheritance);
  RUN_DEMO(demo_virtual_inheritance);

  return EXIT_SUCCESS;
}