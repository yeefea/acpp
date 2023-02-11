# Container



## sequenial container

- vector
- list
- forward_list
- string

```c++

// 类型
container<T>::iterator
container<T>::const_iterator
container<T>::size_type

// 迭代器
c.begin()  
c.end()
c.rbegin()
c.rend()
*it
it->x
++it
iter1 == iter2
iter1 != iter2

// 构造
container<T> c;
container<T> c(c2);  // 拷贝初始化
container<T> c(n);  // 初始化n个元素
container<T> c(n, t); // 初始化n个元素t的拷贝
container<T> c(begin_iter, end_iter); // 用两个迭代器之间的元素初始化

// 其他操作
c=c2
// 增
c.insert(d, begin_iter, end_iter)  // 把begin,end之间的元素拷贝到d之前
c.push_back(t)
// 删
c.erase(iter)  // 注意vector和string删除操作会让该位置之后的iterator都失效。list会让删除位置的iterator失效，erase会返回新的iter
c.erase(begin_iter, end_iter)

// 查
c.size()
c.empty()  // 容器是否为空
c[n]

```

## vector

```c++
v.reserve(n);  // 预留n个元素的空间，类似于make([]xxx, 0, n)

v.resize(n);

```

## list

```c++

l.sort()
l.sort(cmp)

```

## string

```c++
#include <cctype>
// isspace(c) true if c is a whitespace character.
// isalpha(c) true if c is an alphabetic character.
// isdigit(c) true if c is a digit character.
// isalnum(c) true if c is a letter or a digit.
// ispunct(c) true if c is a punctuation character.
// isupper(c) true if c is an uppercase letter.
// islower(c) true if c is a lowercase letter.
// toupper(c) Yields the uppercase equivalent to c
// tolower(c) Yields the lowercase equivalent to c
```