#include <string>
class HasPtr
{

public:
  HasPtr(const std::string &s = std::string()) : ps(new std::string(s)) {}
  HasPtr(const HasPtr &p) : ps(new std::string(*p.ps)) {} // 1 拷贝构造
  HasPtr &operator=(const HasPtr &rhs)                    // 2 拷贝赋值
  {
    delete ps;
    ps = new std::string(*rhs.ps);
    return *this;
  }
  ~HasPtr() { delete ps; }              // 3 析构
  HasPtr(HasPtr &&p) noexcept {}        // 4 移动构造
  HasPtr &operator=(const HasPtr &&rhs) // 5 移动赋值
  {
    delete ps;
    ps = new std::string(*rhs.ps);
    return *this;
  }

  std::string *ps = nullptr;
};

struct NoCopy
{

  NoCopy() = default;
  NoCopy(const NoCopy &) = delete;
  NoCopy &operator=(const NoCopy &) = delete;

private:
  int field1;
};