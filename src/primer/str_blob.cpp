#include "str_blob.h"
#include "str_blob_ptr.h"
StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}

StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {}

void StrBlob::check(size_type i, const std::string &msg) const
{
  if (i >= data->size())
  {
    throw std::out_of_range(msg);
  }
}

std::string &StrBlob::front()
{
  check(0, "front on empty blob");
  return data->front();
}

StrBlobPtr StrBlob::begin()
{
  return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end()
{
  auto ret = StrBlobPtr(*this, data->size());
  return ret;
}

std::string &StrBlob::back()
{
  check(0, "back on empty blob");
  return data->back();
}

void StrBlob::pop_back()
{
  check(0, "pop_back on empty blob");
  return data->pop_back();
}
