#include <iostream>
#include <thread>  // 线程库

void hello() { std::cout << "Hello Concurrent World\n"; }

int main() {
  std::thread t(hello);
  t.join();
}
