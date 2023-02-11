# Chapter 4

## const

```c++

const vector<double> 和 const vector<const double> 一样，常向量，向量本身和值都不能改

vector<const double> 和 vector<double> 一样

```

## overloading

```c++

double grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(double midterm, double final, const vector<double> &hw)
{
    if (hw.size() == 0)
    {
        throw domain_error("student has done no homework");
    }
    return grade(midterm, final, median(hw));
}
```

## reference

- 函数参数为非const引用，实参必须为lvalue
- 函数参数为const引用或者值传递，实参可以为lvalue或非lvalue

## exception

```c++

/*
logic_error domain_error invalid_argument
length_error out_of_range runtime_error
range_error overflow_error underflow_error
*/

e.what() // 相当于Go的e.Error()

```


## library


```c++

// stream

s.width(n)

setw(n)

```