#include "ch2.h"
#include <string>
#include <iterator>
#include <memory>
#include <cstdlib>

#include "utils.h"

std::new_handler X::current_handler;

void X::outofmemory()
{
  std::cerr << "X outofmemory" << std::endl;
  abort(); // 一定要abort，否则这个函数会被反复调用
}

std::new_handler X::set_new_handler(std::new_handler p)
{
  std::new_handler old_hdl = current_handler;
  current_handler = p;
  return old_hdl;
}

void *X::operator new(size_t size)
{
  std::cout << "try allocate X[" << size << "]" << std::endl;
  std::new_handler g_hdl = std::set_new_handler(current_handler);
  void *memory;
  try
  {
    memory = ::operator new(size);
  }
  catch (std::bad_alloc &e)
  {
    std::set_new_handler(g_hdl);
    throw;
  }

  std::set_new_handler(g_hdl);
  return memory;
}
void *X::operator new[](size_t size)
{
  std::cout << "try allocate X[" << size << "]" << std::endl;
  // set global handler to custom handler
  std::new_handler g_hdl = std::set_new_handler(current_handler);
  void *memory;
  try
  {
    // call global new
    memory = ::operator new(size);
  }
  catch (std::bad_alloc &e)
  {
    // recover global handler
    std::set_new_handler(g_hdl);
    throw;
  }
  // recover global handler
  std::set_new_handler(g_hdl);
  return memory;
}

void demo_new_delete()
{
  constexpr int sz = 100;
  std::string *sarr = new std::string[sz];

  describe_array(sarr, sarr + sz);

  delete[] sarr;

  typedef std::string addresslines[4];
  std::string *pal = new addresslines; // 这里看不出是数组了
  delete[] pal;                        // 依然要[]不然就内存泄露，很迷，所以千万不要typedef数组!!!
}

// global_oom_handler new-handler函数 void (*)()
void global_oom_handler()
{
  std::cerr << "oops, oom! (global scope)" << std::endl;
  abort();
}

// demo_new_handler 自定义new handler
void demo_new_handler()
{
  constexpr size_t sz = 922337203685477;
  // std::set_new_handler(global_oom_handler);
  // int *pi = new int[sz];  // oom global scope
  // delete[] pi;

  X::set_new_handler(X::outofmemory);
  X *p = new X;
  delete p;
  // class specific

  Y::set_new_handler([]() -> void
                     { std::cout << "allocate Y error" << std::endl;
                     // 一定要abort
                    abort(); });
  Y *py = new Y[sz];
  delete[] py;
}

int main()
{
  RUN_DEMO(demo_new_delete);
  RUN_DEMO(demo_new_handler);

  // global_oom_handler();
}