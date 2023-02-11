## iterator

- vector
- list
- forward_list

### vector
```c++
// 在迭代vector的同时erase，需要将erase的返回值赋给iter！！！！！
vector<Student_info> fail;
vector<Student_info>::iterator iter = students.begin();
while (iter != students.end())
{
    if (fgrade(*iter))
    {
        fail.push_back(*iter);
        // 删除操作会让旧的iter失效！！！！！
        iter = students.erase(iter);  // 注意这里很关键！！！！！
    }
    else
    {
        ++iter;
    }
}

```

### list

```c++

list<Student_info> students;

students.sort(compare); // list 有自己的sort函数

// list erase更快，因为无需移动后面的元素，但是list随机访问很慢
list<Student_info> extract_fails4(list<Student_info> &students)
{
    list<Student_info> fail;
    list<Student_info>::iterator iter = students.begin();
    while (iter != students.end())
    {
        if (fgrade(*iter))
        {
            fail.push_back(*iter);
            iter = students.erase(iter); // 注意这里很关键！！！！！
        }
        else
        {
            ++iter;
        }
    }
    return fail;
}


```