#pragma once
#include <string>

class Screen
{
public:
    // typedef std::string::size_type pos;
    using pos = std::string::size_type; // 等价
    Screen() = default;
    Screen(pos ht, pos wd, char c)
        : height(ht), width(wd), contents(ht * wd, c) {}
    char get() const
    {
        return contents[cursor];
    }
    inline char get(pos ht, pos wd) const;

private:
    mutable size_t access_ctr;
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
};
