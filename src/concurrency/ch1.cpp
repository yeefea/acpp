#include <iostream>
#include <thread> // 线程库
#include <pthread.h>
#include <unistd.h>
#include <chrono>

static int parentCPU;
static int childCPU;
static int nloops;

void hello()
{

  auto pid = getpid();
  auto tid = std::this_thread::get_id();
  auto t = pthread_self();
  std::cout << "child pid: " << pid << std::endl;
  std::cout << "child tid: " << tid << " " << t << std::endl;

  cpu_set_t set;
  CPU_ZERO(&set);
  CPU_SET(childCPU, &set);
  if (sched_setaffinity(0, sizeof(set), &set) == -1)
  {
    std::cerr << "child sched_setaffinity error" << std::endl;
    return;
  }

  volatile int sum = 0;
  for (int j = 0; j < nloops; j++)
  {
    sum += 1;
  }
  std::cout << "child sum: " << sum << std::endl;
}

int main(int argc, char **argv)
{
  if (argc != 4)
  {
    fprintf(stderr, "Usage: %s parent-cpu child-cpu num-loops\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  parentCPU = atoi(argv[1]);
  childCPU = atoi(argv[2]);
  nloops = atoi(argv[3]);

  auto tid = std::this_thread::get_id();
  auto pid = getpid();
  auto t = pthread_self();
  std::cout << "Hello Concurrent World" << std::endl;
  std::cout << "pid: " << pid << std::endl;
  std::cout << "tid: " << tid << " " << t << std::endl;

  cpu_set_t set;
  CPU_ZERO(&set);
  CPU_SET(parentCPU, &set);
  sched_setaffinity(0, sizeof(set), &set);
  if (sched_setaffinity(getpid(), sizeof(set), &set) == -1)
  {
    std::cerr << "main sched_setaffinity error" << std::endl;
    return EXIT_FAILURE;
  }
  std::thread th(hello);
  volatile int sum = 0;
  for (int j = 0; j < nloops; j++)
  {
    sum += 1;
  }
  std::cout << "main sum: " << sum << std::endl;
  th.join();
  return EXIT_SUCCESS;
}
