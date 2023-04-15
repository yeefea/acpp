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


## 模板实参推断

