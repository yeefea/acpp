#include <iostream>
#include <stdexcept>
#include <vector>
#include <iterator>
#include <algorithm>
// 一开始忘记include <vector>会报奇怪的错
// 错误提示最后一行缺少分号，很迷

using std::back_inserter;
using std::cout;
using std::domain_error;
using std::endl;
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
    // input iterator
    // read only
    vector<int> vec = {1, 2, 3, 4, 5, 6};

    auto loc = my_find(vec.begin(), vec.end(), 3);

    cout << "[ " << *loc << " ]" << endl;
}

template <typename In, typename Out>
Out my_copy(In begin, In end, Out dest)
{
    // write only iterator
    // *it = x
    // ++it
    while (begin != end)
    {
        *dest++ = *begin++; // 这里dest一般是back_inserter
    }
    return dest;
}

void demo_output_iterator()
{

    vector<int> vec = {1, 2, 3, 4, 5, 6}, new_vec;

    my_copy(vec.begin(), vec.end(), back_inserter(new_vec));

    describe_vector(vec);     // original
    describe_vector(new_vec); // copy
}

template <typename For, typename X>
void my_replace(For beg, For end, const X &a, const X &b)
{
    // forward iterator
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

    // bidirectional iterator
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

template <class Ran, class X>
bool my_binary_search(Ran begin, Ran end, const X &x)
{
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
}

int main()
{
    demo1();
    demo_describe();

    /*

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
    return 0;
}