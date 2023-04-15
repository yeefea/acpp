#pragma once
#include <initializer_list>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

// 函数try语句块
template <typename T>
class DemoConstructorObj {
 public:
  DemoConstructorObj(std::initializer_list<T> il) try
      : data(std::make_shared<std::vector<T>>(il)) {
    throw std::runtime_error("construct failed");
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
    // 注意，构造函数这里就算catch了异常，还是会重新抛出
  }

  ~DemoConstructorObj() try {
    throw std::runtime_error("destruct failed");
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }

 private:
  std::shared_ptr<std::vector<T>> data;
};

void function_with_try_block() try {
  std::cout << "demo function-try block" << std::endl;
  throw std::runtime_error("function_with_try_block failed");
} catch (const std::exception &e) {
  std::cout << e.what() << std::endl;
}

class MyError : public std::runtime_error {
 public:
  explicit MyError(const std::string &s) : std::runtime_error(s) {}
};