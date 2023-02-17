#include <iostream>
#include <stdexcept>
#include <vector>
#include <iterator>
#include <algorithm>
// 一开始忘记include <vector>会报奇怪的错
// 错误提示最后一行缺少分号，很迷

// 第8章 模板函数

using std::back_inserter;
using std::cin;
using std::cout;
using std::domain_error;
using std::endl;
using std::find_if;
using std::istream_iterator; // <iterator>
using std::ostream_iterator; // <iterator>
using std::string;
using std::swap;
using std::vector;

template <typename T>
void describe_vector(const std::vector<T> &items)
{
    cout << "[ ";
    auto iter = items.begin();

    if (iter != items.end())
    {
        cout << *iter;
        ++iter;
        for (; iter != items.end(); ++iter)
        {
            cout << ", " << *iter;
        }
    }

    cout << " ] size: " << items.size() << endl;
}

template <typename T>
T median(vector<T> v)
{
    // 注意使用范型类型中定义的类型需要typename关键字！！！
    typedef typename vector<T>::size_type vec_sz;
    vec_sz size = v.size();
    if (size == 0)
    {
        throw domain_error("median of an empty vector");
    }

    sort(v.begin(), v.end());

    vec_sz mid = size / 2;
    return size % 2 == 0 ? (v[mid] + v[mid - 1]) / 2 : v[mid];
}

template <typename In, typename X>
In find(In begin, In end, const X &x)
{
    while (begin != end && *begin != x)
        ++begin;
    return begin;
}

template <typename T>
T max(const T &left, const T &right)
{
    return left > right ? left : right;
}

void demo1()
{

    double a = 0.0;
    double b = 1.0;
    double c = max(a, b);

    cout << a << " " << b << " " << c << endl;
}

void demo_describe()
{

    vector<int> vec = {};
    describe_vector(vec);
    vec = {1};
    describe_vector(vec);
    vec = {1, 2};
    describe_vector(vec);
    vec = {1, 2, 3};
    describe_vector(vec);
    vec = {1, 2, 3, 4, 5};
    describe_vector(vec);
}

template <typename In, typename X>
In my_find(In begin, In end, const X &x)
{
    while (begin != end && *begin != x)
        ++begin;
    return begin;
}

void demo_input_iterator()
{
    // 只读迭代器支持的操作
    // input iterator
    // read only
    vector<int> vec = {1, 2, 3, 4, 5, 6};

    auto loc = my_find(vec.begin(), vec.end(), 3);

    cout << "[ " << *loc << " ]" << endl;
}

template <typename In, typename Out>
Out my_copy(In begin, In end, Out dest)
{
    // 只写迭代器支持的操作
    // write only iterator
    // *it = x
    // ++it
    while (begin != end)
    {
        *dest++ = *begin++; // 这里dest一般是back_inserter
    }
    return dest;
}

bool space(char c)
{
    return isspace(c);
}
bool not_space(char c)
{
    return !isspace(c);
}
template <typename Out>
void my_split(const string &str, Out os)
{
    typedef string::const_iterator iter;
    iter i = str.begin();
    while (i != str.end())
    {
        i = find_if(i, str.end(), not_space);

        iter j = find_if(i, str.end(), space);
        if (i != str.end())
        {
            *os++ = string(i, j); // 写入迭代器
        }
        i = j;
    }
}

void demo_output_iterator()
{

    vector<int> vec = {1, 2, 3, 4, 5, 6}, new_vec;

    my_copy(vec.begin(), vec.end(), back_inserter(new_vec));

    describe_vector(vec);     // original
    describe_vector(new_vec); // copy

    vector<string> strs;
    my_split("abc defg azx", back_inserter(strs));
    describe_vector(strs);
}

template <typename For, typename X>
void my_replace(For beg, For end, const X &a, const X &b)
{
    // 前向（读写）迭代器支持的操作 forward iterator
    // read-writer iterator

    // *it read and write
    // ++it and it++
    // it==j and it != j
    // it->member
    while (beg != end)
    {
        if (*beg == a)
        {
            *beg = b;
        }
        ++beg;
    }
}

void demo_forward_iterator()
{
    vector<int> vec = {1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1};
    describe_vector(vec);
    my_replace(vec.begin(), vec.end(), 3, -3);
    describe_vector(vec);
}

template <typename Bi>
void my_reverse(Bi begin, Bi end)
{

    // 双向迭代器支持的操作bidirectional iterator
    // --iter
    // iter--
    while (begin != end)
    {
        --end;
        if (begin != end)
        {
            swap(*begin++, *end);
        }
    }
}

void demo_bidirectional_iterator()
{

    vector<int> vec = {1, 2, 3, 4, 5, 6, 7};
    describe_vector(vec);
    my_reverse(vec.begin(), vec.end());
    describe_vector(vec);
}

template <typename Ran, typename X>
bool my_binary_search(Ran begin, Ran end, const X &x)
{
    // 随机迭代器支持的操作
    // p + n, p - n, and n + p
    // p - q
    // p[n] (equivalent to *(p + n))
    // p < q, p > q, p <= q, and p >= q
    while (begin < end)
    {
        // find the midpoint of the range
        Ran mid = begin + (end - begin) / 2;
        // see which part of the range contains x; keep looking only in that part
        if (x < *mid)
            end = mid;
        else if (*mid < x)
            begin = mid + 1;
        // if we got here, then *mid == x so we're done
        else
            return true;
    }
    return false;
}
void demo_random_iterator()
{
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    bool exist0 = my_binary_search(vec.begin(), vec.end(), 0);
    bool exist3 = my_binary_search(vec.begin(), vec.end(), 3);

    cout << "0 exists? " << exist0 << endl;
    cout << "3 exists? " << exist3 << endl;
}

void demo_io_iterator()
{

    cout << "input some numbers:" << endl;
    vector<int> v;
    copy(
        istream_iterator<int>(cin),
        istream_iterator<int>(), // default value = EOF
        back_inserter(v));

    describe_vector(v);
    copy(
        v.begin(), v.end(), ostream_iterator<int>(cout));
    cout << endl;
}

int main()
{
    demo1();
    demo_describe();

    /*
    5种迭代器：只读，只写，读写，双向读写，随机读写
    Input iterator: Sequential access in one direction, input only
    Output iterator: Sequential access in one direction, output only
    Forward iterator: Sequential access in one direction, input and output
    Bidirectional iterator: Sequential access in both directions, input and output
    Random-access iterator: Efficient access to any element, input and output
    */
    demo_input_iterator();
    demo_output_iterator();
    demo_forward_iterator();
    demo_bidirectional_iterator();
    demo_random_iterator();
    demo_io_iterator();
    return 0;
}