#include <cstddef>
#include <fstream>  // 文件流
#include <iostream>
#include <vector>

#include "Student_info.h"
#include "util.h"

using namespace std;

int add1(int a) { return a + 1; }

void demo_pointer() {
  // 指针
  int *p, q;

  q = 42;

  p = &q;

  *p = 21;

  cout << "*p=" << (*p) << " and q=" << q << endl;
}

typedef double (*analysis_fp)(const vector<Student_info> &);

double median_student_info(const vector<Student_info> &students) {
  // some code here
  return 0.0;
}

double avg_student_info(const vector<Student_info> &students) {
  // some code here
  return 1.0;
}

analysis_fp get_analysis_ptr(string op) {
  if (op == "median") {
    return median_student_info;
  } else {
    return avg_student_info;
  }
}

typedef double (*aggfunc)(const vector<double> &);

double median_double(const vector<double> &nums) {
  // some code here
  return 0.0;
}

double avg_double(const vector<double> &nums) {
  // some code here
  return 1.0;
}

aggfunc get_agg_func(string op) {
  if (op == "median") {
    return median_double;
  }
  return avg_double;
}

// 这什么东西啊。。。TODO
// https://zhuanlan.zhihu.com/p/561716560
double (*DC(double (*)(double)))(double);

void demo_function_pointer() {
  // 函数指针
  int (*fp)(int);  // int fp(int)
  fp = add1;       // 等价于 fp=&add1;
  auto a = fp(1);  // 等价于 (*fp)(1)

  cout << "a=" << a << endl;

  auto md = get_agg_func("median");
  auto res = md({1, 2, 3, 4});
  cout << "median=" << res << endl;
}

template <typename In, typename Pred>
In my_find_if(In begin, In end, Pred f) {
  while (begin != end && !f(*begin)) {
    ++begin;
  }
  return begin;
}

bool is_negative(int n) { return n < 0; }

void demo_iterator() {
  vector<int> v = {1, 2, 3, -4, 5};
  vector<int>::iterator i = my_find_if(v.begin(), v.end(), is_negative);
  cout << "negative number: " << *i << endl;
}

const size_t NDim = 3;  // size_t from <cstddef>

// 声明
template <typename T>
void describe_array(T *arr, size_t size);

void demo_array() {
  double coords[NDim];
  *coords = 1.5;
  *(coords + 1) = 2.3;
  describe_array(coords, NDim);

  // array to vector
  vector<double> vd(coords, coords + NDim);
  describe_vector(vd);

  auto p = coords, q = coords + NDim;
  ptrdiff_t diff = q - p;  // <cstddef>
  cout << "pointer diff: " << diff << endl;

  const int month_lengths[] = {
      31, 28, 31, 30, 31, 30,  // we will deal elsewhere with leap years
      31, 31, 30, 31, 30, 31};

  describe_array(month_lengths,
                 sizeof(month_lengths) / sizeof(month_lengths[0]));
}

// 定义
template <typename T>
void describe_array(T *arr, size_t size) {
  for (size_t i = 0; i < size; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
}

size_t my_strlen(const char *p) {
  size_t size = 0;
  while (*p++ != '\0') ++size;
  return size;
}
void demo_string() {
  // 等价于 "Hello"
  const char hello_stupid[] = {'H', 'e', 'l', 'l', 'o', '\0'};
  string hello(hello_stupid, hello_stupid + my_strlen(hello_stupid));

  auto len = my_strlen(hello_stupid);
  cout << hello << " strlen: " << len << endl;
}

string letter_grade(double grade) {
  static const double numbers[] = {97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0};
  static const char *const letters[] = {"A+", "A", "A-", "B+", "B", "B-",
                                        "C+", "C", "C-", "D",  "F"};

  static const size_t ngrades = sizeof(numbers) / sizeof(*numbers);

  for (size_t i = 0; i < ngrades; ++i) {
    if (grade >= numbers[i]) return letters[i];
  }
  return "???";
}

void demo_array_of_char_ptr() {
  vector<int> scores = {94, 60, 85};
  for (vector<int>::const_iterator iter = scores.begin(); iter != scores.end();
       ++iter) {
    cout << "score " << *iter << " is " << letter_grade(*iter) << endl;
  }
}

void demo_const_ptr() {
  /*
  const int * 和 int *const 的区别

  */
  int i = 1;
  int j = 2;
  const int *ptrc = &i;  // 指向常量的指针  (const int) *ptrc
  ptrc = &j;             // ok, the pointer itself is a variable
  // *ptr = 2; // invalid, since ptrc is a pointer to constant
  int *const cptr = &i;  // 指针常量 (int*) const cptr
  // cptr = &j; invalid, cptr itself is a constant
  *cptr = 3;  // ok, cptr itsenf is a contant, but the value it refers to is a
              // variable and can be changed.

  cout << "ptr to const: " << *ptrc << ", const ptr: " << *cptr << endl;
}

void demo_clog_cerr() {
  clog << "some log" << endl;
  cerr << "some error" << endl;
}

int *one_factory() { return new int(1); }

char *duplicate_chars(const char *p) {
  size_t len = strlen(p) + 1;
  char *result = new char[len];
  copy(p, p + len, result);
  return result;
}

int *get_static_integer() {
  static int i = 123;
  return &i;
}

void demo_static_alloc() {
  auto i = get_static_integer();

  cout << "static int pointer: " << *i << endl;
}

void demo_dynamic_alloc() {
  int *p = new int(42);  // malloc
  ++(*p);
  cout << "malloc: " << *p << " ";
  delete p;  // free

  p = one_factory();
  cout << "malloc: " << *p << endl;
  delete p;  // free a single object

  const size_t sz = 10;
  double *dp = new double[sz];
  // for (int i = 0; i < sz; i++)
  // {
  //     *(dp + i) = i;
  // }
  vector<double> v(dp, dp + sz);

  describe_vector(v);
  delete[] dp;  // free an array

  const char some_str[] = "some stringssss!";
  char *s2 = duplicate_chars(some_str);
  cout << s2 << endl;
  delete[] s2;
}

void demo_fstream() {
  string filename = "tmp.txt";
  ofstream outfile(filename);
  // ofstream outfile(filename.c_str()); 也可以
  string content = "some text hahaha";
  outfile << content << endl;
  outfile << content << endl;
  outfile << content << endl;

  ifstream infile(filename);
  // ifstream infile(filename.c_str()); 也可以

  string new_content = "";
  if (infile) {
    cout << "read from input file:" << endl;
    while (getline(infile, new_content)) {
      cout << new_content << endl;
    }
  } else {
    cout << "can not open file: " << filename << endl;
  }
}
int main(int argc, char **argv) {
  // 命令行参数
  // argv[0]是可执行文件名
  for (int i = 0; i < argc; ++i) {
    cout << argv[i] << " ";
  }
  cout << endl;

  demo_pointer();
  demo_function_pointer();
  demo_iterator();
  demo_array();
  demo_string();
  demo_array_of_char_ptr();
  demo_const_ptr();
  demo_clog_cerr();
  demo_fstream();
  demo_static_alloc();
  demo_dynamic_alloc();

  return 0;
}