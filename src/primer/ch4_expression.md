## 运算符优先级

- 一共16级
- 只有level 3和15是右到左结合，其余都是左到右
- level 3 典型运算符：前置++ --，正负号 + -，逻辑非！，取地址&，解引用*，new delete，cast ()
- level 15 典型运算符：赋值运算符 + 三元condition + throw

- level 1 最高优先级 ::

- level 16 最低优先级 ,

- level 2 次高优先级 11种
成员访问  . ->
函数调用  ()
下标      []
后缀      ++ --
type id
4种cast static_cast, const_cast, reinterpret_cast, dynamic_cast

- level 3

- level 15 次低优先级，赋值运算符 + 三元condition + throw
= *= /= %= += -= <<= >>= &= |= ^= ?: throw

1 == 2 ? 1 : 1 == 1 ? 2 : 3 右结合是为了要模拟if-elseif-else，答案是2

### ++ --
- 后置++ -- 是level 2，左到右结合。i++返回右值，所以不能写i++++。
- 前置++ -- 是level 3，右到左结合，++i返回左值，所以可以写++++i。