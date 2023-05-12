#include <thread>
#include <cstdlib>
#include <chrono>
#include <iostream>

inline uint64_t current_ts()
{
  return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

int main(int argc, char **argv)
{
  uint64_t t0, t1;
  for (int i = 0; i < 20; ++i)
  {
    t0 = current_ts();
    std::this_thread::yield();
    t1 = current_ts();
    // avg 200+ ns
    std::cout << (double)(t1 - t0) << std::endl;
  }

  return EXIT_SUCCESS;
}