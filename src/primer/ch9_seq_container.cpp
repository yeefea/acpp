#include <array>
#include <cstdint>
#include <deque>
#include <forward_list>
#include <list>
#include <string>
#include <vector>
#include <array>
#include <stack>
#include <queue>
#include "utils.h"

/*
10 templates

vector
deque
list
forward_list
array
string

stack
queue
priority_queue

*/

void demo_vector()
{
  // ch3
  std::vector<int> ivec;
  std::vector<std::vector<std::string>> file;
  std::vector<std::string> svec(10, "sss");

  // std::vector<int&> ref_vec; 不行，没有引用的vector，引用不是对象

  std::vector<int> ivec2{10};
  std::vector<std::string> svec2{10};

  describe_sequential_container(ivec2.begin(), ivec2.end());
  describe_sequential_container(svec2.begin(), svec2.end());

  LOG(svec[0]);

  describe_vector(svec);
}

void demo_deque()
{
  std::deque<int> q = {1, 2, 3, 4, 5};

  q.push_back(6);
  q.push_front(0);

  describe_sequential_container(q.begin(), q.end());
}

void demo_list()
{
  std::list<std::string> sl = {"111", "222", "333"};
  describe_sequential_container(sl.begin(), sl.end());
}

void demo_array()
{

  std::array<int, 10> iarr = {1, 2, 3, 4}; // 后6个数字是0，默认初始化
  decltype(iarr) iarr2(iarr);              // copy constructor

  iarr[8] = 10000;
  describe_sequential_container(iarr.begin(), iarr.end());
  iarr.swap(iarr2);
  describe_sequential_container(iarr.begin(), iarr.end());
  describe_sequential_container(iarr2.begin(), iarr2.end());
}

void demo_assign()
{
  std::array<int, 10> iarr = {1, 2, 3, 4}; // 后6个数字是0，默认初始化
  std::vector<int> ivec(10);

  ivec.assign(iarr.begin(), iarr.end());
  describe_sequential_container(iarr.begin(), iarr.end());
  describe_sequential_container(ivec.begin(), ivec.end());

  std::list<std::string> names(10);
  describe_sequential_container(names.begin(), names.end());
  std::vector<const char *> old_style = {"111", "222", "333", "444"};
  describe_sequential_container(old_style.begin(), old_style.end());

  // names的内容和old_styles一样了，长度也一样
  names.assign(old_style.begin(), old_style.end());

  describe_sequential_container(names.begin(), names.end());
}

void demo_swap()
{

  std::vector<int> ivec(10);
  std::vector<int> ivec2{1, 2, 3, 4, 5, 6};
  describe_sequential_container(ivec.begin(), ivec.end());
  describe_sequential_container(ivec2.begin(), ivec2.end());

  // 一般都用非成员版本
  std::swap(ivec, ivec2);
  describe_sequential_container(ivec.begin(), ivec.end());
  describe_sequential_container(ivec2.begin(), ivec2.end());
}

void demo_insert()
{

  std::vector<int> ivec{1, 2, 3, 4, 5, 6};
  ivec.insert(ivec.begin(), 123);
  ivec.insert(ivec.end(), 666);
  describe_sequential_container(ivec.begin(), ivec.end());

  std::list<int> ilst{11, 22, 33, 44};
  // 把一个元素添加到头部
  ilst.insert(ilst.begin(), 333);
  // 把ivec的所有元素添加到尾部
  ilst.insert(ilst.end(), ivec.begin(), ivec.end());
  describe_sequential_container(ilst.begin(), ilst.end());
}

void demo_forward_list()
{

  std::list<int> ilst{11, 22, 33, 44};

  std::forward_list<int> flist;

  // 从头部添加，无法从尾部添加
  flist.insert_after(flist.before_begin(), 123);
  flist.insert_after(flist.before_begin(), ilst.begin(), ilst.end());

  describe_sequential_container(flist.begin(), flist.end());

  auto prev = flist.before_begin();
  auto curr = flist.begin();
  while (curr != flist.end())
  {
    if (*curr % 2)
    {
      // erase odd numbers
      curr = flist.erase_after(prev);
    }
    else
    {
      prev = curr;
      ++curr;
    }
  }
  describe_sequential_container(flist.begin(), flist.end());
}

void demo_resize()
{

  std::vector<int> ivec{1, 2, 3, 4, 5, 6};
  describe_sequential_container(ivec.begin(), ivec.end());

  // shink to 3
  ivec.resize(3);
  describe_sequential_container(ivec.begin(), ivec.end());
}

void demo_string()
{
  std::string s = "hello world";

  auto s2 = s.substr(0, 5);
  auto s3 = s.substr(6);
  auto s4 = s.substr(6, 111);

  LOG(s);
  LOG(s2);
  LOG(s3);
  LOG(s4);

  s.insert(s.size(), 5, '!');
  LOG(s);

  s.insert(s.end(), 5, '-');
  LOG(s);

  s.replace(11, 3, "Fifth"); // 删3个，插入5个字符
  LOG(s);

  LOG(std::to_string(123123));
  LOG(std::stoi("12345"));
  LOG(std::stol("12345"));
  LOG(std::stoul("12345"));
  LOG(std::stoll("12345"));
  LOG(std::stoull("12345"));

  LOG(std::stof("12345.1"));
  LOG(std::stod("12345.2"));
  LOG(std::stold("12345.3"));
}

void demo_stack()
{

  std::deque<int> deq = {1, 2, 3, 4};
  std::stack<decltype(deq)::value_type> stk(deq);
  LOG(stk.top());
  stk.push(123);
  LOG(stk.top());
  stk.pop();

  std::stack<std::string, std::vector<std::string>> str_stk;
  str_stk.push("aaa");
  LOG(str_stk.top());
  str_stk.push("bbb");
  LOG(str_stk.top());
  str_stk.pop();
  LOG(str_stk.top());
}

void demo_queue()
{

  // 默认是大顶堆
  std::priority_queue<int> prio_q;

  prio_q.push(2);
  LOG(prio_q.top()); // 2
  prio_q.push(3);
  LOG(prio_q.top()); // 3
  prio_q.push(1);
  LOG(prio_q.top()); // 3

  prio_q.pop();
  LOG(prio_q.top());
  prio_q.pop();
  LOG(prio_q.top());
  prio_q.pop();

  // greater函数，实现小顶堆
  std::priority_queue<int, std::vector<int>, std::greater<int>> min_q;
  min_q.push(2);
  LOG(min_q.top()); // 2
  min_q.push(3);
  LOG(min_q.top()); // 2
  min_q.push(1);
  LOG(min_q.top()); // 1

  // functor
  struct
  {
    bool operator()(const std::string &s1, const std::string &s2) const { return s1.size() > s2.size(); }
  } cmp_str;

  std::priority_queue<std::string, std::vector<std::string>, decltype(cmp_str)> str_q(cmp_str);

  str_q.push("22");
  LOG(str_q.top());
  str_q.push("1");
  LOG(str_q.top());
  str_q.push("333");
  LOG(str_q.top());

  auto fn = [](const std::string &s1, const std::string &s2) -> bool
  { return s1.size() > s2.size(); };

  std::priority_queue<std::string, std::vector<std::string>, decltype(fn)> str_q2(fn);
}

int main(int argc, char **argv)
{
  RUN_DEMO(demo_vector);
  RUN_DEMO(demo_deque);
  RUN_DEMO(demo_list);
  RUN_DEMO(demo_array);
  RUN_DEMO(demo_assign);
  RUN_DEMO(demo_swap);
  RUN_DEMO(demo_insert);
  RUN_DEMO(demo_forward_list);
  RUN_DEMO(demo_resize);
  RUN_DEMO(demo_string);
  RUN_DEMO(demo_stack);
  RUN_DEMO(demo_queue);
}