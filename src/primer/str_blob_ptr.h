#pragma once
#include <memory>
#include <vector>
#include <string>

#include "str_blob.h"

class StrBlobPtr
{
public:
  StrBlobPtr() : curr(0) {}
  StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
  std::string &deref() const; // 解引用
  StrBlobPtr &incr();         // 前缀递增 ++x

private:
  // 检查wptr是否有效
  std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string &) const;
  std::weak_ptr<std::vector<std::string>> wptr; // weak pointer
  std::size_t curr;
};