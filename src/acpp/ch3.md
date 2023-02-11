# Chapter 3

## 类型转换

int和unsigned int运算的时候，会把int隐式转为usigned int，要注意原来的int变量不能为负数，否则会计算错误


## 用例

```c++
#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>
using std::cin; 
using std::sort;
using std::cout;
using std::streamsize;
using std::endl;
using std::string;
using std::setprecision;
using std::vector;

typedef <type> <new_type_name>;

// vector相关

vector<T> v;

vector<T>::size_type

v.push_back()
v.begin()
v.end()
v[i]
v.size()

// 迭代
for (auto it = v.begin(); it != v.end(); it++){
    // *it ....
}


// algorithm

sort(begin, end)
max(e1, e2)


// io
while (cin >> x)
{
    // ...
}

s.precision()
s.precision(n)
setprecision(n)
streamsize // 这个类型是setprecision的参数，precision的返回类型

```