#include <string>
#include "window_mgr.h"
#include "screen.h"

void WindowMgr::clear(ScreenIndex i)
{
  Screen &s = screens[i];
  s.contents = std::string(s.height * s.width, ' ');
}

// 注意返回类型还是需要类名前缀，因为ScreenIndex是在WindowMgr内部定义的
WindowMgr::ScreenIndex WindowMgr::addScreen(const Screen &s)
{
  screens.push_back(s);
  return screens.size() - 1;
}
