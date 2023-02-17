# template

```c++

// 定义模板函数
template<typename T1, typename T2> T1 zero( ) {return 0};

// 使用泛型参数里面定义的类型需要加typename关键字
typename T::size_type sz;
```

## 迭代器
5种迭代器
- input 只读，顺序访问
- output 只写，顺序访问
- forward 读写，顺序访问
- bidirectional 读写，双向访问
- random-access 读写，随机访问
