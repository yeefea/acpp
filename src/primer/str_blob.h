#pragma once

#include <string>
#include <vector>
#include <memory>
#include <initializer_list>
#include <stdexcept>

class StrBlobPtr;

class StrBlob
{
  friend class StrBlobPtr;

public:
  typedef typename std::vector<std::string>::size_type size_type;

  StrBlob();
  StrBlob(std::initializer_list<std::string> il);
  size_type size() const { return data->size(); }
  bool empty() const { return data->empty(); }
  void push_back(const std::string &t) { data->push_back(t); }
  void pop_back();
  StrBlobPtr begin();
  StrBlobPtr end();

  std::string &front();
  std::string &back();

private:
  std::shared_ptr<std::vector<std::string>> data;
  void check(size_type i, const std::string &msg) const;
};
