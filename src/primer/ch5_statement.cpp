#include <iostream>
#include <string>
#include <stdexcept>
#include "utils.h"

void demo_switch_statement()
{

  unsigned aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0;

  std::string user_input("abasdgiausglkasdkgjaoiusdlflkasdgbiuwef");
  for (auto &c : user_input)
  {
    switch (c)
    {
    case 'a':
      /* code */
      ++aCnt;
      break;
    case 'e':
      ++eCnt;
      break;
    case 'i':
      ++iCnt;
      break;
    case 'o':
      ++oCnt;
      break;
    case 'u':
      ++uCnt;
      break;
    }
  }

  std::cout << OUTPUT_VAL(aCnt) << std::endl;
  std::cout << OUTPUT_VAL(eCnt) << std::endl;
  std::cout << OUTPUT_VAL(iCnt) << std::endl;
  std::cout << OUTPUT_VAL(oCnt) << std::endl;
  std::cout << OUTPUT_VAL(uCnt) << std::endl;
}

void demo_range_for()
{

  std::vector<int> ivec = {
      1,
      2,
      3,
      4,
      5,
      6,
      7,
      8,
  };
  describe_vector(ivec);
  for (auto &x : ivec)
  {
    x *= x;
  }
  describe_vector(ivec);
}

void demo_do_while()
{
  int i = 0;
  do
  {
    std::cout << "do while run only once!" << std::endl;
  } while (i != 0);
}

void demo_jump()
{
  // break: for, while, do-while, switch
  // continue: for, while, do-while
  // goto:
  int i = 0;

  while (1)
  {
    while (1)
    {
      while (1)
      {
        if (i == 100)
        {
          goto end;
        }
        ++i;
      }
    }
  }

  goto end;

end:
  std::cout << "return" << std::endl;
  return;
}

void panic()
{
  throw std::runtime_error("panic");
}

void demo_try()
{

  try
  {
    panic();
  }
  catch (std::runtime_error err)
  {
    std::cout << "error: " << err.what() << std::endl;
    // throw; // 可以继续抛出异常
  }
}

int main(int argc, char **argv)
{
  RUN_DEMO(demo_switch_statement);
  RUN_DEMO(demo_range_for);
  RUN_DEMO(demo_do_while);
  RUN_DEMO(demo_jump);
  RUN_DEMO(demo_try);
  return EXIT_SUCCESS;
}
