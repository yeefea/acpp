#pragma once
#include <string>
#include "window_mgr.h"
class Screen
{
    // friend class WindowMgr;
    friend void WindowMgr::clear(ScreenIndex);

public:
    // typedef <OldType> <NewType>
    // typedef std::string::size_type pos;
    // using <NewType> = <OldType>
    using pos = std::string::size_type; // 等价于typedef
    Screen() = default;
    Screen(pos ht, pos wd, char c)
        : height(ht), width(wd), contents(ht * wd, c) {}
    char get() const
    {
        ++access_ctr;
        return contents[cursor];
    }
    inline char get(pos ht, pos wd) const;
    Screen &move(pos r, pos c);
    Screen &set(pos r, pos c, char ch);
    Screen &display(std::ostream &os)
    {
        do_display(os);
        return *this;
    }
    const Screen &display(std::ostream &os) const
    {
        do_display(os);
        return *this;
    }

private:
    mutable size_t access_ctr; // 在const函数里也能修改mutable成员
    pos cursor{0};             // 类内初始化，用{}
    pos height = 0, width = 0; // 类内初始化，用=
    std::string contents;
    void do_display(std::ostream &os) const { os << contents; }
};

inline Screen &Screen::move(pos r, pos c)
{
    pos row = r * width;
    cursor = row + c;
    return *this;
}

// 在声明的时候就是inline，这里不用重复
char Screen::get(pos r, pos c) const
{
    ++access_ctr;
    pos row = r * width;
    return contents[row + c];
}
inline Screen &Screen::set(pos r, pos c, char ch)
{
    contents[r * width + c] = ch;
    return *this;
}