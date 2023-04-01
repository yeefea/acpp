#include "str_vec.h"

StrVec::StrVec(const StrVec &s)
{
  auto newdata = alloc_n_copy(s.begin(), s.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

// 移动构造函数，接管右值引用，“窃取”，一般要指定noexcept不抛异常
StrVec::StrVec(StrVec &&s) noexcept
    : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
  s.elements = s.first_free = s.cap = nullptr;
}
StrVec &StrVec::operator=(StrVec &&rhs) noexcept
{
  if (this != &rhs) // 需要处理自赋值
  {
    free();
    elements = rhs.elements;
    first_free = rhs.first_free;
    cap = rhs.cap;
    rhs.elements = rhs.first_free = rhs.cap = nullptr; // 清空右侧对象
  }
  return *this;
}
StrVec::~StrVec()
{
  free();
}

StrVec &StrVec::operator=(const StrVec &rhs) &
{
  auto data = alloc_n_copy(rhs.begin(), rhs.end());
  free(); // 释放现有内存
  elements = data.first;
  first_free = cap = data.second;
  return *this;
}

// void StrVec::reallocate()  // copy
// {
//   auto newcapacity = size() ? 2 * size() : 1;
//   auto newdata = alloc.allocate(newcapacity);
//   auto dest = newdata;
//   auto elem = elements;
//   for (size_t i = 0; i != size(); ++i)
//   {
//     alloc.construct(dest++, std::move(*elem++)); // 移动构造, string管理的内存不会被拷贝
//   }
//   free();
//   elements = newdata;
//   first_free = dest;
//   cap = elements + newcapacity;
// }
void StrVec::reallocate()
{

  auto newcapacity = size() ? 2 * size() : 1;
  auto first = alloc.allocate(newcapacity);

  // 普通迭代器返回左值引用，移动迭代器返回右值引用
  auto last = std::uninitialized_copy(
      std::make_move_iterator(begin()),
      std::make_move_iterator(end()),
      first); // 用移动构造函数初始化内存
  free();     // 释放旧空间
  elements = first;
  first_free = last;
  cap = elements + newcapacity;
}

void StrVec::push_back(const std::string &s)
{
  chk_n_alloc();
  alloc.construct(first_free++, s);
}

void StrVec::push_back(std::string &&s)
{
  chk_n_alloc();
  alloc.construct(first_free++, std::move(s));
}

std::pair<std::string *, std::string *>
StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
  auto data = alloc.allocate(e - b);
  return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
  // 释放全部内存
  if (elements)
  {
    for (auto p = first_free; p != elements;)
    {
      alloc.destroy(--p);
    }
    alloc.deallocate(elements, cap - elements);
  }
}