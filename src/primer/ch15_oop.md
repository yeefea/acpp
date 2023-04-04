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