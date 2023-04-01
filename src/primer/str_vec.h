#pragma once

#include <string>
#include <memory>

class StrVec
{

public:
  StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
  StrVec(const StrVec &);
  // 引用限定符 &左值 &&右值，必须同时出现在声明和定义中
  // 如果同时有const和&，const必须在前，像const &这样
  StrVec &operator=(const StrVec &) &;
  ~StrVec();
  StrVec(StrVec &&) noexcept;               // 移动构造函数
  StrVec &operator=(StrVec &&rhs) noexcept; // 移动赋值

  void push_back(const std::string &); // 拷贝push_back
  void push_back(std::string &&);      // 移动push_back，提升性能

  size_t size() const { return first_free - elements; }
  size_t capacity() const { return cap - elements; }
  std::string *begin() const { return elements; }
  std::string *end() const { return first_free; }

private:
  static std::allocator<std::string> alloc;
  void chk_n_alloc()
  {
    if (size() == capacity())
    {
      reallocate();
    }
  }
  std::pair<std::string *, std::string *> alloc_n_copy(const std::string *, const std::string *);
  void free();
  void reallocate();
  std::string *elements;   // begin
  std::string *first_free; // end
  std::string *cap;        // capacity
};