#include <algorithm>
#include <cctype>
#include <deque>
#include <functional>  // bind
#include <iterator>    // iterators
#include <list>
#include <numeric>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "utils.h"

void demo_algo() {
  // find in vector
  std::vector<int> ivec = {1, 2, 3, 4, 5, 6, 6, 7, 32};

  auto it = std::find(ivec.cbegin(), ivec.cend(), 42);

  bool found = it != ivec.cend();
  LOG(found);  // false
  it = std::find(ivec.cbegin(), ivec.cend(), 32);

  found = it != ivec.cend();
  LOG(found);  // true

  // find in array
  int ia[] = {2423, 232312, 12312, 1111, 149, 32};
  auto pi = std::find(std::begin(ia), std::end(ia), 32);
  found = pi != std::end(ia);
  LOG(found);

  // count in vector
  auto cnt = std::count(ivec.cbegin(), ivec.cend(), 6);
  LOG(cnt);
}

void demo_readonly_algo() {
  std::vector<double> dvec1 = {1.0, 2.0, 3.0, 4.4, 5.6};
  // acc
  int sum = std::accumulate(dvec1.cbegin(), dvec1.cend(), 0.0);
  LOG(sum);

  std::vector<std::string> svec = {"abc", "efg", "xyz"};
  // 注意下面最后一个参数只能用string，不能用字面值，因为const
  // char*没有operator+
  std::string initstr = "<prefix>";
  auto jstr = std::accumulate(svec.cbegin(), svec.cend(), initstr);
  LOG(initstr);
  LOG(jstr);

  // equal
  decltype(dvec1) dvec2 = {1.0, 2.0, 3.0, 4.4};
  // 短的vector放前面
  bool eq = std::equal(dvec2.cbegin(), dvec2.cbegin(), dvec1.cbegin());
  LOG(eq);
}

void demo_modify_algo() {
  std::vector<double> dvec1(10, 123.0);
  describe_sequential_container(dvec1.cbegin(), dvec1.cend());

  // fill
  std::fill(dvec1.begin(), dvec1.begin() + dvec1.size() / 2, 0.01);
  describe_sequential_container(dvec1.cbegin(), dvec1.cend());

  // fill_n
  std::fill_n(dvec1.begin() + dvec1.size() / 2, 3, 0.03);
  describe_sequential_container(dvec1.cbegin(), dvec1.cend());
}

void demo_back_inserter() {
  std::vector<int> ivec1;
  describe_vector(ivec1);

  // back_inserter, 类似于append操作
  auto it = std::back_inserter(ivec1);

  for (int i = 100; i < 110; ++i) {
    *it = i;  // append i
  }

  *it = 123;  // append 123
  describe_vector(ivec1);

  // fill_n + back_inserter
  std::fill_n(std::back_inserter(ivec1), 10, 0);  // append 0 0 0 0 0 0 0 0 0 0
  describe_vector(ivec1);
}
void demo_copy() {
  int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  decltype(a1) a2;

  describe_array(std::begin(a1), std::end(a1));
  describe_array(std::begin(a2), std::end(a2));

  // copy a1 -> a2
  auto ret = std::copy(std::begin(a1), std::end(a1), a2);
  describe_array(std::begin(a2), std::end(a2));

  // copy + back_inserter
  std::vector<int> ivec;
  std::copy(std::cbegin(a1), std::cend(a1), std::back_inserter(ivec));
  describe_vector(ivec);
}

void demo_replace() {
  int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  describe_array(std::begin(a1), std::end(a1));

  // 4 -> 42
  std::replace(std::begin(a1), std::end(a1), 4, 42);
  describe_array(std::begin(a1), std::end(a1));
}

void demo_rearrange() {
  std::vector<std::string> svec = {"a",     "fox", "red", "quick",
                                   "jumps", "a",   "hill"};
  describe_vector(svec);
  // unique先要sort
  std::sort(svec.begin(), svec.end());
  describe_vector(svec);
  // unique
  auto end_unique = std::unique(svec.begin(), svec.end());
  describe_vector(svec);
  // 删掉[end_unique, end)区间内的元素
  svec.erase(end_unique, svec.end());
  describe_vector(svec);
}

void demo_lambda() {
  // lambda expr
  // [cap list] (param list) -> return type {function body}
  // [cap list] (param list) {function body}

  // binary predicate
  auto shorter = [](const std::string &a, const std::string &b) -> bool {
    return a.size() < b.size();
  };

  std::vector<std::string> svec = {"a",     "fox", "red", "quick",
                                   "jumps", "a",   "hill"};
  describe_vector(svec);
  std::stable_sort(svec.begin(), svec.end(), shorter);
  describe_vector(svec);
  // 从长到短排序
  std::stable_sort(
      svec.begin(), svec.end(),
      std::bind(shorter, std::placeholders::_2, std::placeholders::_1));
  describe_vector(svec);

  // find_if
  const size_t sz = 4;
  auto word_it =
      std::find_if(svec.cbegin(), svec.cend(),
                   [sz](const std::string &a) { return a.size() > sz; });
  if (word_it == svec.cend()) {
    std::cout << "word not found" << std::endl;
  } else {
    std::cout << "first word whose size > 4: " << *word_it << std::endl;
  }

  // for_each
  std::for_each(svec.begin(), svec.end(),
                [](std::string &s) { s[0] = toupper(s[0]); });

  std::for_each(svec.cbegin(), svec.cend(),
                [](const std::string &s) { LOG(s); });
}

void demo_lambda_capture() {
  // capture by value
  size_t v1 = 42;
  auto f = [v1] { return v1; };  // 拷贝了v1的值
  v1 = 0;                        // 对f内部的v1没有影响
  auto j = f();
  LOG(v1);
  LOG(j);  // j = 42

  auto v2 = 42;
  // capture by ref
  auto f2 = [&v2] { return v2; };  // v2的引用
  v2 = 0;                          // 这里也改变了f2内部的v2
  auto j2 = f2();
  LOG(v2);
  LOG(j2);  // j = 0

  // implicit capture
  auto f11 = [=] { return v1; };

  auto f22 = [&] { return v2; };

  // mixed implicit capture
  auto f3 = [&, v1] { return v1; };  // v1前必须没有&，其他变量都是value capture

  auto f4 = [=, &v2] { return v2; };  // v2前必须有&，其他值都是ref capture
}

void demo_mutable_lambda() {
  size_t v1 = 42;
  auto f = [v1]() mutable {
    LOG(v1);
    ++v1;
    LOG(v1);
    return v1;
  };
  auto j1 = f();
  v1 = 0;
  LOG(v1);
  LOG(j1);
  auto j11 = f();
  LOG(v1);
  LOG(j11);

  size_t v2 = 42;  // 如果const size_t则f2不能修改v2
  auto f2 = [&v2] { return ++v2; };
  v2 = 0;
  auto j2 = f2();
  LOG(v2);
  LOG(j2);
}
void demo_transform() {
  std::vector<int> vi = {1, 2, 3, 4, 5, 6};
  std::vector<std::pair<int, std::string>> buf;
  std::transform(vi.begin(), vi.end(), std::back_inserter(buf),
                 [](int i) -> decltype(buf)::value_type {
                   return {i, std::to_string(i) + " hahahaha"};
                 });

  for (auto &item : buf) {
    std::cout << item.first << ": " << item.second << std::endl;
  }
}

void some_complex_function(int a, int b, int c, int d, int e) {
  LOG(a);
  LOG(b);
  LOG(c);
  LOG(d);
  LOG(e);
}

void some_ref_function(int &r, const int &cr) {
  LOG(r);
  LOG(cr);
}

// bind important!!!
void demo_bind() {
  // bind, ref, cref

  // bind parameter
  auto check_size = [](const std::string &s, std::string::size_type sz) {
    return s.size() >= sz;
  };
  // _1 第一个参数，_2 第二个参数，以此类推
  auto check3 = std::bind(check_size, std::placeholders::_1, 3);
  std::string s = "123123";
  auto is_valid_str = check3(s);
  LOG(is_valid_str);
  s = "12";
  is_valid_str = check3(s);
  LOG(is_valid_str);

  // rearrange parameter order

  // _1 第一个参数，_2 第二个参数，以此类推
  auto some_new_func =
      std::bind(some_complex_function, 1, 2, std::placeholders::_2, 3,
                std::placeholders::_1);

  some_new_func(100, 200);

  // std::ref, std::cref
  int i = 123;
  const int ci = 124;
  auto some_r_func = std::bind(some_ref_function, std::ref(i), std::cref(ci));
  some_r_func();
}

void demo_iterator() {
  // insert iter

  std::deque<int> q;
  auto back_ins = std::back_inserter(q);
  auto front_ins = std::front_insert_iterator(q);

  for (int i = 0; i < 13; ++i) {
    if (i % 2 == 0) {
      *back_ins = i;
    } else {
      *front_ins = i;
    }
  }

  describe_sequential_container(q.cbegin(), q.cend());

  // stream iter
  // istream
  std::stringstream ss("123 124 a");
  std::istream_iterator<int> int_it(ss), eof;
  while (int_it != eof) {
    auto var = *int_it;
    int_it++;
    LOG(var);
  }

  std::stringstream ss2("1 2 3 4 5");
  int sum = std::accumulate(std::istream_iterator<int>(ss2), eof, 0);
  LOG(sum);

  // ostream

  std::ostream_iterator<double> out_iter(std::cout, " ");
  std::vector<double> dvec = {-1.3, -2.1, 9.5, 8.3};
  for (auto d : dvec) {
    *out_iter++ = d;
  }
  std::cout << std::endl;

  std::copy(dvec.crbegin(), dvec.crend(), out_iter);
  std::cout << std::endl;
  // reverse iter
  describe_sequential_container(q.crbegin(), q.crend());

  std::string line = "abc,defg,xyz";
  auto comma = std::find(line.cbegin(), line.cend(), ',');
  std::cout << std::string(line.cbegin(), comma) << std::endl;

  auto rcomma = std::find(line.crbegin(), line.crend(), ',');
  // .base()把reverse iterator转为forward iterator
  std::cout << std::string(rcomma.base(), line.cend()) << std::endl;

  // move -> ch13
}

void demo_splice() {
  std::list<int> lst1 = {1, 2, 3, 4, 5};
  std::list<int> lst2 = {100, 200};

  describe_sequential_container(lst1.begin(), lst1.end());

  lst1.splice(lst1.end(), lst2);  // lst1 -> lst2

  describe_sequential_container(lst1.begin(), lst1.end());
  describe_sequential_container(lst2.begin(), lst2.end());  // lst2 is empty now
}

int main(int argc, char **argv) {
  RUN_DEMO(demo_algo);
  RUN_DEMO(demo_readonly_algo);
  RUN_DEMO(demo_modify_algo);
  RUN_DEMO(demo_back_inserter);
  RUN_DEMO(demo_copy);
  RUN_DEMO(demo_replace);
  RUN_DEMO(demo_rearrange);
  RUN_DEMO(demo_lambda);
  RUN_DEMO(demo_lambda_capture);
  RUN_DEMO(demo_mutable_lambda);
  RUN_DEMO(demo_transform);
  RUN_DEMO(demo_bind);
  RUN_DEMO(demo_iterator);
  RUN_DEMO(demo_splice);
}