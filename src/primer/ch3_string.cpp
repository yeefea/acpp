#include <cctype>
#include <cstring>
#include <cstddef> // size_t
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "utils.h"

void demo_using()
{
  using std::cout;
  using std::endl;

  cout << "hello using::std" << endl;
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
  std::string s9(std::move(s8));          // 移动构造

  LOG(s1);
  LOG(s2);
  LOG(s22);
  LOG(s222);
  LOG(s3);
  LOG(s33);
  LOG(s4);
  LOG(s5);
  LOG(s6);
  LOG(s7);
  LOG(s8);
  LOG(s9);
}

void describe_string(std::string &s)
{
  static std::string some_s = "12312312";

  // size_type 无符号整数类型
  std::string::size_type sz = s.size();

  std::cout << "string=\"" << s << "\""
            << ", empty? " << s.empty() << ", size? " << sz << ", s==\""
            << some_s << "\"\? " << (s == some_s) << ", s<\"" << some_s
            << "\"\? " << (s < some_s) << std::endl;
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

  describe_string(s);
}

void demo_cctype()
{
  // char type
  std::string s = "abc 123,\n";
  LOG(s);
  for (auto c : s)
  {
    LOG(c);
    LOG(std::isalnum(c));
    LOG(std::isalpha(c));
    LOG(std::iscntrl(c));
    LOG(std::isdigit(c));
    LOG(std::isgraph(c));
    LOG(std::islower(c));
    LOG(std::isprint(c));
    LOG(std::ispunct(c));
    LOG(std::isspace(c));
    LOG(std::isupper(c));
    LOG(std::isxdigit(c));
    LOG(char(std::tolower(c)));
    LOG(char(std::toupper(c)));
    std::cout << std::endl;
  }

  for (auto &c : s)
  {
    c = std::toupper(c);
  }
  LOG(s);
}

void demo_range_for()
{
  // 范围for语句
  std::string str("some string");
  for (auto &c : str)
  {
    c = std::toupper(c);
  }
  std::cout << OUTPUT_VAL(str) << std::endl;
}
void demo_vector_init()
{
  std::vector<int> v1(10);
  std::vector<int> v2{10};
  std::vector<int> v3(10, 1);
  std::vector<int> v4{10, 1};

  LOG_VEC(v1);
  LOG_VEC(v2);
  LOG_VEC(v3);
  LOG_VEC(v4);

  std::vector<std::string> sv1{10, "1"};

  LOG_VEC(sv1);
}
void demo_vector()
{
  std::vector<int> v1; // 默认初始化
  LOG_VEC(v1);
  std::vector<int> v2(v1); // 拷贝初始化
  LOG_VEC(v2);
  std::vector<int> v22 = v1; // 拷贝初始化
  LOG_VEC(v22);
  std::vector<std::string> v3(10, "123.4f"); // 直接初始化
  LOG_VEC(v3);
  std::vector<float> v4(10); // 直接初始化
  LOG_VEC(v4);
  std::vector<double> v5{1.1, 2.2, 3.3, 4.4}; // 列表初始化
  LOG_VEC(v5);
  std::vector<double> v55 = {1.1, 2.2, 3.3, 4.4}; // 列表初始化
  LOG_VEC(v55);

  std::cout << "demo vector move constructor" << std::endl;
  std::vector<double> v6{1.1, 2.2, 3.3};
  LOG_VEC(v6);
  std::vector<double> v66(std::move(v6)); // 移动构造函数
  LOG_VEC(v6);
  LOG_VEC(v66);

  v55.push_back(123.4);
  v55.push_back(5678.9);
  LOG_VEC(v55);

  std::cout << OUTPUT_VAL(v55.empty()) << std::endl;
  std::cout << OUTPUT_VAL(v55.size()) << std::endl;
  v55[3] = 1.3;
  LOG_VEC(v55);
  v55 = v5;
  LOG_VEC(v55);
  v55 = {1.2, 3.4, 5.6};
  LOG_VEC(v55);
  std::cout << OUTPUT_VAL(v55 == v5) << std::endl;
  std::cout << OUTPUT_VAL(v55 != v5) << std::endl;
  std::cout << OUTPUT_VAL(v55 < v5) << std::endl;
  std::cout << OUTPUT_VAL(v55 <= v5) << std::endl;
  std::cout << OUTPUT_VAL(v55 > v5) << std::endl;
  std::cout << OUTPUT_VAL(v55 >= v5) << std::endl;

  std::vector<int> grades = {42, 65, 95, 100, 39, 67, 95,
                             76, 88, 76, 83, 92, 76, 93};
  std::vector<unsigned> scores(11, 0);
  for (auto x : grades)
  {
    ++scores[x / 10];
  }

  LOG_VEC(scores);
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

void demo_array()
{
  constexpr unsigned sz = 42;
  constexpr unsigned szi = 10;
  int arr[szi];
  for (int i = 0; i < szi; ++i)
  {
    arr[i] = i + 100;
  }
  describe_array(arr, arr + szi);
  int *parr[sz];

  std::string strs[sz] = {"hello", " ", "world", "nihao"};
  describe_array(strs, strs + sz);

  // 复杂的数组声明，默认情况下，类型修饰符从右向左绑定，有括号时从内向外绑定
  int *ptrs[szi]; // 含有10个指针的数组
  describe_array(ptrs, ptrs + szi);
  int(*Parray)[szi] = &arr; // 指向int数组的指针
  describe_array(*Parray, *Parray + szi);
  int(&arrRef)[szi] = arr; // int数组的引用
  describe_array(arrRef, arrRef + szi);

  int *(&arry)[szi] = ptrs; // ptrs的引用
  describe_array(arry, arry + szi);

  char *pc = new char[100]; // all initialized to 0
  describe_array(pc, pc + 100);
  delete[] pc;
}

void demo_char_array()
{
  char a1[] = {'c', '+', '+'};
  const char a2[] = {'c', '+', '+', '\0'}; // 注意 C的字符串一定要\0结尾

  std::string s2(a2);
  char a3[] = "c++";
  const char a4[] = "daniel";
}

// demo_pointer_array  指针和数组
void demo_pointer_array()
{
  std::string nums[] = {"one", "two", "three"};
  int ia[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  // auto
  auto ia2(ia);      // 用auto推理出来ia2是指针，而不是数组！
  auto ia22(&ia[0]); // 等价于上一行
  // 指针做迭代器
  describe_array(ia2, ia2 + 9);

  // decltype
  decltype(ia) ia3 = {0, 1, 2, 3, 4,
                      5, 6, 7, 8}; // 用decltype推理推理出来ia3是数组
  ia3[4] = 10;
  describe_array(ia3, ia3 + 9);

  std::string *begin = &nums[0], *end = &nums[3]; // begin
  describe_array(begin, end);

  // 标准库的begin，end函数获取数组首尾地址
  int *beg = std::begin(ia), *last = std::end(ia);

  describe_array(beg, last);

  std::ptrdiff_t diff = last - beg;
  std::cout << OUTPUT_VAL(diff) << std::endl;
}

void demo_cstr()
{
  char s1[] = {'1', '2', '3', '4', '5', '\0'};
  char *bg1 = std::begin(s1), *ed1 = std::end(s1);
  char s2[] = {'6', '7', '8', '9', '\0'};
  char *bg2 = std::begin(s2), *ed2 = std::end(s2);
  LOG(strlen(s1));
  LOG(strlen(s2));

  std::cout << OUTPUT_VAL(std::strcmp(s1, s2)) << std::endl;
  strcpy(s1, s2);
  std::cout << OUTPUT_VAL(s1) << std::endl;

  describe_array(bg1, ed1);
  describe_array(bg2, ed2);

  // std::string -> cstring
  std::string s("Hello world");
  const char *acient_str = s.c_str();
  describe_array(acient_str, acient_str + strlen(acient_str));
}

void demo_multi_dim_array()
{
  // 多维数组
  constexpr int ROW = 3, COL = 4;

  int ia[ROW][COL] = {{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}};
  int cnt = 100;
  // 范围for语句处理多维数组，除了最内层循环以外，都应该用reference
  // 遍历方法1，写起来更容易
  for (auto &r : ia)
  {
    describe_array(std::begin(r), std::end(r));
    for (auto &c : r)
    {
      c = cnt;
      ++cnt;
    }
  }

  // 遍历方法2
  for (auto p = ia; p != ia + ROW; ++p)
  {
    for (auto q = *p; q != *p + COL; ++q)
    {
      std::cout << *q << ' ';
    }
    std::cout << std::endl;
  }

  for (const auto r : ia)
  {
    describe_array(r, r + COL);
  }

  int(*p)[4] = ia;
  p = &ia[2];
  std::cout << OUTPUT_VAL(ia) << " " << OUTPUT_VAL(p) << std::endl;
  describe_array(*p, (*p) + COL);
  int arr[10][20][30] = {0};

  // 类型别名，简化数组定义
  typedef int int_arr[4];
  using int_array = int[4]; // 和上一行等价，而且更直观
  int_array ia2[3];

  for (const auto r : ia2)
  {
    describe_array(r, r + COL);
  }
}

int main(int argc, char **argv)
{
  RUN_DEMO(demo_using);
  RUN_DEMO(demo_initialize_string);
  RUN_DEMO(demo_string_operation);
  RUN_DEMO(demo_cctype);
  RUN_DEMO(demo_range_for);

  RUN_DEMO(demo_vector_init);
  RUN_DEMO(demo_vector);

  RUN_DEMO(demo_iterator);
  RUN_DEMO(demo_array);
  RUN_DEMO(demo_char_array);
  RUN_DEMO(demo_pointer_array);
  RUN_DEMO(demo_cstr);
  RUN_DEMO(demo_multi_dim_array);
  return EXIT_SUCCESS;
}
