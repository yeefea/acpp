# Chapter 7

## friend

### friend member function
```c++
class Screen{
    friend void Window_mgr::clear(ScreenIndex);
};
```

令成员函数作为友元，需要仔细组织代码结构
1. 定义Window_mgr类，其中声明clear函数，但不能定义。
2. 在clear函数使用Screen的成员之前必须先声明Screen
3. 定义Screen，包括声明clear为friend
4. 定义clear函数，使用Screen的成员