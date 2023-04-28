#include "ch2.h"
#include <string>
#include <iterator>
#include <memory>
#include "utils.h"

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

void oom_handler()
{
  std::cout << "oops, oom!" << std::endl;
}

void demo_destructor()
{
  std::set_new_handler(oom_handler);
}

int main()
{
  RUN_DEMO(demo_new_delete);
}