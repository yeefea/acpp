# 自定义类型

```c++
struct A{  // 默认public
private:
    field1 int;
    field2 double;
    field3 std::string;
public:
    A()field1(0),field2(0.0){};  // 构造函数和初始化列表
    //...
};  // 注意有分号

class B{  // 默认private
private:
//...
public:
//...
};  // 注意有分号
```