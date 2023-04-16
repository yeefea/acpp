
## Exceptions


- exception
    - bad_cast
    - bad_alloc
    - runtime_error  在运行时才能检测到的错误
        - overflow_error
        - underflow_error
        - range_error
    - logic_error  程序逻辑错误，可以在代码中发现的错误
        - domain_error
        - invalid_argument
        - out_of_range
        - length_error


## Namespaces

- 通常不把#include放在namespace里
- 模板特例化必须定义在原始模板的namespace里


```c++
namespace std{
    template <> struct hash<SalesData>;
}

template <> struct std::hash<SalesData>
{
    size_T operator()(const Sales_data &s) const{
        return hash<string>()(s.bookNo) ^ hash<unsigned>()(s.units_sold) ^ hash<double>()(s.revenue);
    }
}

// 或者
namespace std{

template <> struct hash<SalesData>
{
    typedef size_t result_type;
    typedef SalesData argument_type;
    size_t operator()(const SalesData& s) const;
};

size_t hash<SalesData>::operator()(const SalesData& s) const{
    return hash<string>()(s.bookNo) ^ hash<unsigned>()(s.units_sold) ^ hash<double>()(s.revenue);
}

}
```

### inline namespace

```c++

inline namespace FifthEd{  // 只需定义一次inline

}

namespace FifthEd{  // 这里也是inline的
    class XXX{};
}

namespace cpp_primer{
    #include "FifthEd.h"
}

cpp_primer::XXX obj;   // 可以直接访问inline namespace中的东西
```

### unnamed namespace

用来取代全局的static，实现全局实体在整个文件中有效，但是文件外不可见。

```c++
namespace local{
    namespace{
        int i;
    }
}

local::i = 42;
```

```c++
int i;

namespace{
    int i;  // 这样是不行的，因为内部的i和全局的i在使用时没有任何区别，有歧义
}

i = 10; // 哪个i？
```

### 使用namespace中的成员


别名
```c++
namespace cpp_primer {
    namespace QueryLib{

    }
}

namespace primer = cpp_primer;
namespace Qlib = cpp_primer::QueryLib;
```

`using` directive，`using`指示

```c++
using std::string;

void some_func(){
    string s = "123";
}
```

