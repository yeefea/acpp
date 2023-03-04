#include <string>
#include <iostream>
#include "utils.h"

void demo_using()
{
  using std::cout;
  using std::endl;

  cout << "hello using" << endl;
  // 头文件不要using
  // 不要using namespace
}

void demo_string()
{

  std::string s1;
  std::string s2 = s1;
  std::string s22(s1);
  std::string s222(s1.begin(), s1.end());
  std::string s3("hi ya");
  std::string s33 = "hi ya";
  std::string s4(10, 'c');

  std::cout << OUTPUT_VAL(s1) << " "
            << OUTPUT_VAL(s2) << " "
            << OUTPUT_VAL(s22) << " "
            << OUTPUT_VAL(s222) << " "
            << OUTPUT_VAL(s3) << " "
            << OUTPUT_VAL(s33) << " "
            << OUTPUT_VAL(s4) << std::endl;
}

int main(int argc, char **argv)
{
  RUN_DEMO(demo_using);
  RUN_DEMO(demo_string);

  return EXIT_SUCCESS;
}
