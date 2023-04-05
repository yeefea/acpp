## `virtual`

- `virtual`修饰的成员在运行时动态绑定，否则在编译期静态绑定，无法实现多态。
- 任何构造函数以外的非`static`函数都可以`virtual`，`static`函数不能`virtual`


## `protected`
- 子类能访问
- 用户不能访问


## 派生类调用父类构造函数

```c++

BulkQuote::BulkQuote(const std::string& book, double p, std::size_t, double disc)
    :Quote(book, p), min_qty(qty), discount(disc)
{
    // ...
}
```

## `static`成员

```c++
class Base{
public:
    static void statmem();
};

class Derived: public Base{
    void f(const Derived& d)
    {
        // 可以用类名调用
        // 可以用对象名调用
        // 可以用this指针调用
        // 下面4种调用方式都可以！
        Base::statmem();
        Derived::statmem();
        d.statmem();
        statmem();
    }
};
```


## 派生类声明
```c++
class Bird;  // 声明的时候不能写继承列表

class Bird : public Animal{
    // ...
};
```


## 基类

```c++
class Quote{

};

// 继承的时候基类必须已经定义
// class Quote; 这样是不行的
class BulkQuote: public Quote
{
    // ...
};
```

## `final`类
不能被继承，和Java一样

```c++
class NoDerived final
{
    // ...
};
```

## 类型转换


```c++
BulkQuote bulk;
Quote *itemP = &bulk;  // up-casting，隐式转换
BulkQuote *bulkP = static_cast<BulkQuote*>(itemP);  // down-casting
```

```c++
BulkQuote bulk;
// 下面的类型转换通常不是多态的up-casting，而是slicing-down，通常不是期望的行为
Quote item(bulk);
item = bulk;
```

## `virtual` function

- 一旦某个函数被声明为虚函数，则在派生类中都是虚函数
- 不需要重复声明`virtual`

## `override`

- 用来标记子类中覆盖了父类的函数

## `final` function

```c++
struct D2: B{
    void f1(int) const final;
};

struct D3: D2{
    // void f1(int) const;  这样是不行的，因为f1是final函数
};

```

## 强行调用基类的函数
```c++
double undiscounted = baseP->Quote::net_price(42);
```

## 抽象基类
- 含有纯虚函数的类是abstract base class
- 无法创建abstract class的对象（和Java一样）

### 纯虚函数
```c++
class DiscQuote: public Quote{
public:
    double net_price(std::size_t) const = 0;  // 纯虚函数
protected:
// ...
};
```

## `public`, `protected`, `private`, `friend`

### 类型转换

```
B <- D <- E
```
- 只有D public继承B时，用户可以D转B
- D任意继承B，D的成员和friend都能使用D转B
- D需要public或protected继承，E才能使用D转B

总的来说，如果基类的公有成员是可访问的，则派生类向基类的类型转换是可行的。


### `friend`和继承
- 友元关系不能继承
- 基类的友元不能随意访问派生类
- 友元的基类或派生类不能随意访问声明该友元的类

### 改变个别成员的可访问性
`using`关键字

```c++
class Base{
public:
    std::size_t size() const {return n;}
protected:
    std::size_t n;
};

class Derived: private Base{
public:
    using Base::size;  // using改变可访问性
protected:
    using Base::n;
};

```

### 默认继承可访问性
```c++

class Base{
    // ...
};

struct D1: Base{};  // public
class D2: Base{};  // private

```

## 作用域

- 派生类的作用域**嵌套**在基类作用域内

## 名字查找步骤
调用`p->men()或obj.mem()`，查找`mem`的步骤

1. 确定静态类型
2. 在静态类型对应的类中查找`mem`，如果找不到，去基类依次查找，如果找到顶了也找不到，报错。
3. 如果找到`mem`，进行类型检查，确认调用是否合法
4. 如果调用合法
    - 如果`mem`是虚函数，且通过引用或指针调用，则将在运行时确定运行函数的哪个版本
    - 否则在编译期确定调用的函数

派生类的成员不会重载基类的同名函数，而是会覆盖基类的同名成员，即使函数参数不同，也会覆盖。

```c++
struct Base{
    int memfcn();
};

struct Derived: Base{
    int memfcn(int); // 覆盖了基类的memfcn
};

Base b;
Derived d;

d.memfcn(10);
d.Base::memfcn();  // 只能这样调用
```


子类虽然可以覆盖父类的非虚函数，变成虚函数，但是这样写很迷

```c++
struct NonVirtualBase
{
  void some_func() // 这个是non-virtual method，编译期绑定
  {
    std::cout << "NonVirtualBase::some_func()" << std::endl;
  }
  void another_func() // 这个是non-virtual method，编译期绑定
  {
    std::cout << "NonVirtualBase::another_func()" << std::endl;
  }
};

struct VirtualDerived : public NonVirtualBase
{

  virtual void some_func() // 子类虽然可以覆盖父类的non-virtual method，但是这样写会迷糊
  {
    std::cout << "VirtualDerived::some_func()" << std::endl;
  }
  virtual void another_func(int i)
  {
    std::cout << "VirtualDerived::another_func(" << i << ")" << std::endl;
  }
};
```

## 覆盖重载的函数

`using`函数名，导入同名函数的所有重载版本，然后覆盖其中少数几个。不`using`的话需要手工覆盖同名的所有重载版本，很烦。

## 继承拷贝控制
### 虚析构函数
- 父类的virtual destructor在子类析构时会自动被调用。
- 最佳实践：有虚函数的类必须定义虚析构函数
- 在有析构函数的时候，编译器不会合成移动操作

### 合成拷贝控制

规则很复杂，反正就是编译器觉得合成有风险或者合成不了，就不合成，具体看书吧。


### 移动操作
```c++
// 5 rules
class Quote{
public:
    Quote() = default;
    Quote(const Quote&) = default;              // 1
    Quote(Quote&&) = default;                   // 2
    Quote& operator=(const Quote&) = default;   // 3
    Quote& operator=(Quote&&) = default;        // 4
    virtual ~Quote() = default;                 // 5
};


class Base{};
class D: public Base{
public:
    D(const D& d): Base(d){}        // 显式调用基类拷贝构造函数
    D(D&& d):Base(std::move(d)){}   // 显式调用基类移动构造函数
};
```


### 派生类的赋值运算符

需要显式调用
```c++
D &D::operator=(const D& rhs){
    Base::operator=(rhs);
    return *this;
}
```

### 派生类的析构函数

```c++
struct DemoObjDestructorBase
{
  virtual ~DemoObjDestructorBase()
  {
    // 析构的时候会固定调用DemoObjDestructorBase::print
    print();
  }
  virtual void print()
  {
    std::cout << "DemoObjDestructorBase destructor" << std::endl;
  }
};

struct DemoObjDestructorDerived1 : public DemoObjDestructorBase
{
  virtual ~DemoObjDestructorDerived1()
  {
    // 析构的时候会固定调用DemoObjDestructorDerived1::print
    print();
  }
  void print() override
  {
    std::cout << "DemoObjDestructorDerived1 destructor" << std::endl;
  }
};

struct DemoObjDestructorDerived2 : public DemoObjDestructorDerived1
{
  virtual ~DemoObjDestructorDerived2()
  {
    // 析构的时候会固定调用DemoObjDestructorDerived2::print
    print();
  }
  void print() override
  {
    std::cout << "DemoObjDestructorDerived2 destructor" << std::endl;
  }
};
```

### `using`基类构造函数

- `using`构造函数不管出现在哪，总是保持在基类中定义的访问级别
- `explicit`和`constexpr`会被继承下来
- 继承的构造函数逻辑上等价于`derived(params) : base(params) {}`

```c++
class BulkQuote: public DiscQuote{
public:
    using Disc::DiscQuote;
    //...
};

// 等价于
class BulkQuote: public DiscQuote{
public:
    BulkQuote(const std::string& book, double price, std::size_t qty, double disc)
        :DiscQuote(book, price, qty, disc){}
    //...
};
```

## 容器和继承


## 模拟虚拷贝

自定义虚函数`clone`