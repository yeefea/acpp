#include <string>
#include <iostream>
#include <cctype>
#include <vector>
#include "utils.h"

void demo_using()
{
  using std::cout;
  using std::endl;

  cout << "hello using" << endl;
  // 头文件不要using
  // 不要using namespace
}

void demo_initialize_string()
{

  std::string s1;                         // 默认初始化
  std::string s2 = s1;                    // 拷贝初始化
  std::string s22(s1);                    // 拷贝初始化
  std::string s222(s1.begin(), s1.end()); // 直接初始化
  std::string s3("hi ya");                // 直接初始化
  std::string s33 = "hi ya";              // 拷贝初始化
  std::string s4(10, 'c');                // 直接初始化
  std::string s5 = "hiya";                // 拷贝初始化
  std::string s6("hiya");                 // 直接初始化
  std::string s7(10, 'c');                // 直接初始化
  std::string s8 = std::string(10, 'c');  // 创建临时对象再拷贝给s8，多此一举

  std::cout << OUTPUT_VAL(s1) << " "
            << OUTPUT_VAL(s2) << " "
            << OUTPUT_VAL(s22) << " "
            << OUTPUT_VAL(s222) << " "
            << OUTPUT_VAL(s3) << " "
            << OUTPUT_VAL(s33) << " "
            << OUTPUT_VAL(s4) << " "
            << OUTPUT_VAL(s5) << " "
            << OUTPUT_VAL(s6) << " "
            << OUTPUT_VAL(s7) << " "
            << OUTPUT_VAL(s8) << std::endl;
}

void desc_string(std::string &s)
{

  static std::string some_s = "12312312";

  // size_type 无符号整数类型
  std::string::size_type sz = s.size();

  std::cout << "string=\"" << s << "\""
            << ", empty? " << s.empty()
            << ", size? " << sz
            << ", s==\"" << some_s << "\"\? " << (s == some_s)
            << ", s<\"" << some_s << "\"\? " << (s < some_s)
            << std::endl;
  s += some_s;

  std::cout << s << std::endl;
  s = some_s + s;
  std::cout << s << std::endl;
}

void demo_string_operation()
{

  std::string s;

  std::getline(std::cin, s); // line中不包含换行符
  std::cout << s << std::endl;
  s.clear();

  std::cin >> s;
  std::cout << s << std::endl;

  desc_string(s);
}

void demo_cctype()
{

  std::string s = "abc 123,\n";
  std::cout << s << std::endl;
  for (auto c : s)
  {
    std::cout << OUTPUT_VAL(c) << " "
              << OUTPUT_VAL(std::isalnum(c)) << " "
              << OUTPUT_VAL(std::isalpha(c)) << " "
              << OUTPUT_VAL(std::iscntrl(c)) << " "
              << OUTPUT_VAL(std::isdigit(c)) << " "
              << OUTPUT_VAL(std::isgraph(c)) << " "
              << OUTPUT_VAL(std::islower(c)) << " "
              << OUTPUT_VAL(std::isprint(c)) << " "
              << OUTPUT_VAL(std::ispunct(c)) << " "
              << OUTPUT_VAL(std::isspace(c)) << " "
              << OUTPUT_VAL(std::isupper(c)) << " "
              << OUTPUT_VAL(std::isxdigit(c)) << " "
              << OUTPUT_VAL(char(std::tolower(c))) << " "
              << OUTPUT_VAL(char(std::toupper(c))) << " "
              << std::endl;
  }

  for (auto &c : s)
  {
    c = std::toupper(c);
  }

  std::cout << s << std::endl;
}

void demo_vector()
{
  std::vector<int> ivec = {1, 2, 3, 4, 5};
  describe_vector(ivec);
}
int main(int argc, char **argv)
{
  RUN_DEMO(demo_using);
  RUN_DEMO(demo_initialize_string);
  RUN_DEMO(demo_string_operation);
  RUN_DEMO(demo_cctype);
  RUN_DEMO(demo_vector);
  return EXIT_SUCCESS;
}
