#include <string>
#include <iostream>
#include <cctype>
#include <vector>
#include <sstream>
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

  std::string s = "abcabc\nbbbzzz";

  std::stringstream ss(s);

  std::getline(ss, s); // line中不包含换行符
  std::cout << s << std::endl;
  s.clear();

  ss >> s;
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

void demo_range_for()
{
  std::string str("some string");
  for (auto &c : str)
  {
    c = std::toupper(c);
  }
  std::cout << OUTPUT_VAL(str) << std::endl;
}

void demo_vector()
{

  std::vector<int> v1; // 默认初始化
  describe_vector(v1);
  std::vector<int> v2(v1); // 拷贝初始化
  describe_vector(v2);
  std::vector<int> v22 = v1; // 拷贝初始化
  describe_vector(v22);
  std::vector<std::string> v3(10, "123.4f"); // 直接初始化
  describe_vector(v3);
  std::vector<float> v4(10); // 直接初始化
  describe_vector(v4);
  std::vector<double> v5{1.1, 2.2, 3.3, 4.4}; // 列表初始化
  describe_vector(v5);
  std::vector<double> v55 = {1.1, 2.2, 3.3, 4.4}; // 列表初始化
  describe_vector(v55);

  v55.push_back(123.4);
  v55.push_back(5678.9);
  describe_vector(v55);

  std::cout << OUTPUT_VAL(v55.empty()) << std::endl;
  std::cout << OUTPUT_VAL(v55.size()) << std::endl;
  v55[3] = 1.3;
  describe_vector(v55);
  v55 = v5;
  describe_vector(v55);
  v55 = {1.2, 3.4, 5.6};
  describe_vector(v55);
  std::cout << OUTPUT_VAL(v55 == v5) << std::endl;
  std::cout << OUTPUT_VAL(v55 != v5) << std::endl;
  std::cout << OUTPUT_VAL(v55 < v5) << std::endl;
  std::cout << OUTPUT_VAL(v55 <= v5) << std::endl;
  std::cout << OUTPUT_VAL(v55 > v5) << std::endl;
  std::cout << OUTPUT_VAL(v55 >= v5) << std::endl;

  std::vector<int> grades = {42, 65, 95, 100, 39, 67, 95, 76, 88, 76, 83, 92, 76, 93};
  std::vector<unsigned> scores(11, 0);
  for (auto x : grades)
  {
    ++scores[x / 10];
  }

  describe_vector(scores);
}

void demo_iterator()
{
  std::string s = "some string";

  for (auto iter = s.begin(); iter != s.end(); ++iter)
  {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;
}

template <typename T>
void descrive_array(T *begin, T *end)
{
  std::cout << "[";
  auto iter = begin;
  if (iter != end)
  {
    std::cout << *iter;
    ++iter;
  }
  for (; iter != end; ++iter)
  {
    std::cout << ", " << *iter;
  }
  std::cout << "] size: " << (end - begin) << std::endl;
}

template <>
void descrive_array(std::string *begin, std::string *end)
{
  std::cout << "[";
  auto iter = begin;
  if (iter != end)
  {
    std::cout << "\"" << *iter << "\"";
    ++iter;
  }
  for (; iter != end; ++iter)
  {
    std::cout << ", \"" << *iter << "\"";
  }
  std::cout << "] size: " << (end - begin) << std::endl;
}

void demo_array()
{
  constexpr unsigned sz = 42;
  constexpr unsigned szi = 19;
  int arr[szi];
  for (int i = 0; i < szi; ++i)
  {
    arr[i] = i + 100;
  }
  descrive_array(arr, arr + szi);
  int *parr[sz];
  std::string strs[sz] = {"hello", " ", "world", "nihao"};
  descrive_array(strs, strs + sz);
}

void demo_char_array()
{
  char a1[] = {'c', '+', '+'};
  const char a2[] = {'c', '+', '+', '\0'}; // 注意 C的字符串一定要\0结尾

  std::string s2(a2);
  char a3[] = "c++";
  const char a4[] = "daniel";
}

void demo_pointer_array()
{
}
int main(int argc, char **argv)
{
  RUN_DEMO(demo_using);
  RUN_DEMO(demo_initialize_string);
  RUN_DEMO(demo_string_operation);
  RUN_DEMO(demo_cctype);
  RUN_DEMO(demo_range_for);
  RUN_DEMO(demo_vector);
  RUN_DEMO(demo_iterator);
  RUN_DEMO(demo_array);
  RUN_DEMO(demo_char_array);
  RUN_DEMO(demo_pointer_array);
  return EXIT_SUCCESS;
}
