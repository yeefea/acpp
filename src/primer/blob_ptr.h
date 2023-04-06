#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

template <typename T>
class BlobPtr {
 public:
  BlobPtr() : curr(0) {}
  BlobPtr(BlobPtr& a, std::size_t sz = 0) : wptr(a.data), curr(sz) {}
  T& operator*() const {
    auto p = check(curr, "deref past end");
    return (*p)[curr];
  }

  BlobPtr& operator++();  // 在类的内部可以省略掉<T>
  BlobPtr& operator--();

 private:
  std::shared_ptr<std::vector<T>> check(std::size_t, const std::string&) const;
  std::weak_ptr<std::vector<T>> wptr;
  std::size_t curr;
};