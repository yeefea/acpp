#include <iostream>
#include <thread>

class BackgroundTask {
 public:
  void operator()() const { std::cout << __FUNCTION__ << std::endl; }
};

int main(int argc, char **argv) {
  BackgroundTask tsk;
  std::thread my_thread(tsk);
  my_thread.join();
}
