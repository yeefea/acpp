# 模板

## 函数模板

`template <` + 模板参数列表 + `>`

```c++
template <typename T>
int compare(const T &v1, const T &v2)
{
    // ...
    return 0;
}
```

实例化函数模板
```c++
compare(1, 0);  // 编译器推断T=int
compare<double>(1.3, 1.4);  // 手工推断

```


## 非类型模板参数

必须是常量表达式

- 整数
- 指向对象或函数的指针，指针类型实参必须有静态生存期，或者是nullptr或0。
- 指向对象或函数的左值引用，引用类型实参必须有静态生存期。

```c++
template<unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M])
{
    // ...
    return 0;
}

compare("hi", "mom"); // 编译器推断N=3,M=4

```

## inline, constexpr

必须放在模板参数列表后面

```c++
template <typename T>
inline T min(const T&, const T&);
```

## 函数模板、类模板成员函数通常都放在头文件里

## 类模板

```c++
template <typename T>
class Blob{
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    // ...
};
```

## 实例化类模板

只能显式实例化
```c++
Blob<int> ia = {0,1,2,3,4};
```

## 模板中引用模板类型

```c++
std::shared_ptr<std::vector<T>> data;
```

## 类模板成员函数
```c++
template <typename T>
class Blob{
public:
    Blob(Blob&){}  // 类定义内部的<T>可以省略
    void check(size_type i, const std::string &msg) const;
    Blob& some_member_func(){} // 类定义内部的<T>可以省略
};

// 类外部定义成员函数比较繁琐
template <typename T>
Blob<T>::check(size_type i, const std::string &msg) const{
    //...
}

```

## 模板类和友元

### 相同实参类型做friend
```c++
template <typename> class Blob;
template <typename T> bool operator==(const Blob<T>&, const Blob<T>&);
template <typename T> void some_func(T, T);

template <typename> class BlobPtr;
template <typename T>
class Blob{
    friend class BlobPtr<T>;
    // 注意这里operator==<T>
    friend bool operator==<T>(const Blob<T>&, const Blob<T>&);
    friend void some_func<T>(T, T);
    // ...
};
```

### 特定实例做friend
需要前置声明模板

```c++
template <typename T> class Pal;

class C{  // 普通的非模板类
    friend class Pal<C>;  // Pal的一个实例做friend
};
```

### 所有的实例都是friend
不用前置声明模板
```c++
template <typename T> class C2{
    template <typename X> friend class Pal2;  // Pal2的所有实例都是C2的friend，类型参数必须不同于T
};
```

### 用自己的类型参数做friend
```c++
template <typename T> class Bar{
    friend T;
};
```

## 模板类型别名

- typedef
- using

```c++
typedef Blob<std::string> StrBlob;  // typedef只能定义实例化的版本
```

```c++
// using 很灵活
template<typename T> using twin = std::pair<T,T>;
twin<std::string> authors;

template<typename T> using partNo = std::pair<T, unsigned>;
partNo<std::string> books;
```

## 模板static成员

```c++
template <typename T>
class DemoStaticMember{
public:
    static std::size_t count() const {return ctr;}
private:
    static std::size_t ctr;
};

template <typename T>
size_t DemoStaticMember<T>::ctr = 0;
```

## 模板声明
必须包含模板参数
```c++
template <typename T> T calc(const T&, const T&);  // decl

template <typename TT> TT calc(const TT&, const TT&){  // def
    // ...
}
```


## 类型成员
```c++
template <typename T>
typename T::value_type top(const T& c){
    if (!c.empty()){
        return c.back();
    }
    return typename T::value_type();
}

```

## 默认模板实参

函数
```c++
template <typename T, typename F = std::less<T>>
int compare(...){
    // ...
}
```

类
```c++
template <typename T = int> class Number{
public:
    Numbers(T v = 0): val(v){}
private:
    T val;
};

Number<long double> a;
Number<> b;  // 类模板用默认实参还是需要尖括号<>
```

## 成员模板

不能是虚函数！

普通类的成员模板
```c++
class DebugDelete{
public:
    DebugDelete(std::ostream &s=std::cerr):os(s){}
    template <typename T> void operator()(T *p) const{
        os << "deleting unique_ptr" << std::endl;
        delete p;
    }
private:
    std::ostream &os;
};
```

类模板的成员模板
```c++
template <typename T>
class Blob{
    template <typename It> Blob(It b, It e);

};

template <typename T>  // 类模板形参在前
template <typename It>  // 成员形参在后
Blob<T>::Blob(It b, It e): data(std::make_shared<std::vector<T>>(b,e)){}
```


## 控制实例化
```c++
// application.cpp 声明
extern template class Blob<std::string>;
extern template int compare(const int&, const int&);


// template_build.cpp 实例化，必须链接这个文件才能实例化compare和Blob模板
template int compare(const int&, const int&);
template class Blob<std::string>;
```

实例化定义会实例化所有成员，而不是实例化用到的成员。


## 类型转换


- const: 顶层const会被忽略，无论形参还是实参
- 数组或函数指针:
    - 如果形参不是引用类型，会把数组/函数实参转为指针
    - 数组实参转为首地址指针，函数转为函数指针
    - 形参是引用类型则不能转换类型
    - 其他算数转换、派生类转基类都不能用于模板


```c++
template <typename T> T fobj(T, T);
template <typename T> T fref(const T&, const T&);

std::string s1("a val");
const std::string s2("another val");

fobj(s1, s2);   // ok, ignore top-level const
fref(s1, s2);   // ok, ignore top-level const

int a[10], b[42];
fobj(a, b); // ok, array to int*
// fref(a, b); // compile error 这样是不行的
```

## 显式实参

```c++
template <typename T1, typename T2, typename T3>
T1 sum(T2, T3);

auto val3 = sum<long long>(1, 2L);  // 只要给出第一个类型参数，后面两个会自动推导


template <typename T1, typename T2, typename T3>
T3 sum(T1, T2);

auto val2<long long, int, long> sum(1LL, 2L);  // 最后一个类型参数无法推导，只能把前两个也写上，否则无法编译
```

```c++
long lng;
// compare(lng, 1024); 这样是不行的
compare<long>(lng, 1024);   // ok
compare<int>(lng, 1024);    // ok
```


## 尾置返回类型

```c++
template <typename It>
auto fcn(It beg, It end) 
-> typename std::remove_reference<decltype(*beg)>::type  // 返回拷贝值
{
    return *beg;
}
```

## type_traits

一般用在模板里
```c++
typename type_trait_name<SomeType>::type
```

- remove_reference
- add_const
- add_lvalue_reference
- add_rvalue_reference
- remove_pointer
- add_pointer
- make_signed
- make_unsigned
- remove_extent
- remove_all_extent

## 函数指针

```c++
template <typename T> int compare(const T&, const T&);
int (*pf1)(const int&, const int&) = compare;  // 自动推理出T=int


void func(int(*)(const string&, const string&));
void func(int(*)(const int&, const int&));

// func(compare); 这样不行，有歧义
func(compare<int>);  // ok
```

## 引用形参推断

TODO


## CRTP

```c++
template <typename D>
class Base
{
public:
  void interface() {
    static_cast<D *>(this)->implement();
  }

  static void static_interface() {
    D::static_interface();
  }

  void implement() {
    std::cout << "Base" << std::endl;
  }
};

class DerivedFoo : public Base<DerivedFoo>
{
public:
  void implement() {
    std::cout << "Foo" << std::endl;
  }
  static void static_interface() {
    std::cout << "Static Foo" << std::endl;
  }
};

class DerivedBar : public Base<DerivedBar> {};

int main (int argc, char *argv[])
{
  DerivedFoo foo;
  DerivedBar bar;

  foo.interface();
  foo.static_interface();
  bar.interface();

  return 0;
}
```