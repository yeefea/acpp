#pragma once
#include <vector>
class Screen;

class WindowMgr
{
public:
  using ScreenIndex = std::vector<Screen>::size_type;

  void clear(ScreenIndex);
  ScreenIndex addScreen(const Screen&);

private:
  std::vector<Screen> screens;
};