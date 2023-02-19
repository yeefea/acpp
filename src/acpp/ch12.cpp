
#include <string>
#include <memory>
#include <algorithm>
#include <iterator>
#include <iostream>
using namespace std;
template <typename T>
class Vec
{

public: // interface
    // types
    typedef T *iterator;
    typedef const T *const_iterator;
    typedef size_t size_type;
    typedef T value_type;

    // constructors
    Vec() { create(); }
    // 这里需要explicit，否则单个参数的构造函数会被认为是隐式类型转换
    explicit Vec(size_type n, const T &val = T()) { create(n, val); }
    // copy constructor
    Vec(const Vec &v)
    {
        create(v.begin(), v.end());
    }
    ~Vec() { uncreate(); } // destructor

    //  运算符重载
    // assignment
    // this是lhs，参数是rhs
    Vec &operator=(const Vec &rhs)
    {
        if (&rhs != this) // 检查自赋值
        {
            uncreate();
            create(rhs.begin(), rhs.end());
        }
        return *this;
    }
    // indexing
    T &operator[](size_type i)
    {
        return data[i];
    }

    const T &operator[](size_type i) const // const重载
    {
        return data[i];
    }
    // methods
    size_type size() const
    {
        return limit - data;
    }

    void push_back(const T &val)
    {
        if (avail == limit)
        {
            grow();
        }
        unchecked_append(val);
    }
    void clear()
    {
        uncreate();
    }

    // 迭代器
    iterator begin() { return data; }
    const_iterator begin() const { return data; } // const 重载

    iterator end() { return limit; }
    const_iterator end() const { return limit; } // const 重载

    operator size_t() const
    {
        return size();
    }

private:           // implementation
    iterator data; // begin
    iterator avail;
    iterator limit; // end
    allocator<T> alloc;
    void create();
    void create(size_type, const T &);
    void create(const_iterator, const_iterator);

    void uncreate();
    void grow();
    void unchecked_append(const T &);
};

template <typename T>
void Vec<T>::create()
{
    data = avail = limit = 0;
}
template <class T>
void Vec<T>::create(size_type n, const T &val)
{
    data = alloc.allocate(n); // 分配内存
    limit = avail = data + n;
    uninitialized_fill(data, limit, val);
}
template <class T>
void Vec<T>::create(const_iterator i, const_iterator j)
{
    data = alloc.allocate(j - i); // 分配内存
    limit = avail = uninitialized_copy(i, j, data);
}
template <class T>
void Vec<T>::uncreate()
{
    if (data)
    {
        // destroy (in reverse order) the elements that were constructed
        iterator it = avail;
        while (it != data)
            alloc.destroy(--it);
        // return all the space that was allocated
        alloc.deallocate(data, limit - data);
    }
    // reset pointers to indicate that the Vec is empty again
    data = limit = avail = 0; // nullptr
}
template <class T>
void Vec<T>::grow()
{
    // when growing, allocate twice as much space as currently in use
    size_type new_size = max(2 * (limit - data), ptrdiff_t(1));
    // allocate new space and copy existing elements to the new space
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = uninitialized_copy(data, avail, new_data);
    // return the old space
    uncreate();
    // reset pointers to point to the newly allocated space
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}
// assumes avail points at allocated, but uninitialized space
template <class T>
void Vec<T>::unchecked_append(const T &val)
{
    alloc.construct(avail++, val);
}
template <typename T>
void describe_vec(Vec<T> &v)
{
    for (auto iter = v.begin(); iter != v.end(); iter++)
    {

        cout << (*iter) << " ";
    }
    cout << endl;
}
class Str
{
    friend std::istream &operator>>(std::istream &, Str &); // friend函数
public:
    // typedefs
    typedef Vec<char>::size_type size_type;

    // constructor
    Str() {}
    Str(size_type n, char c) : data(n, c) {}

    Str(const char *cp)
    {
        copy(cp, cp + strlen(cp), back_inserter(data));
    }

    // 泛型构造函数
    template <typename In>
    Str(In b, In e)
    {
        copy(b, e, back_inserter(data));
    }

    // operators
    // indexing
    char &operator[](size_type i) { return data[i]; }
    const char &operator[](size_type i) const { return data[i]; }
    // +=
    Str &operator+=(const Str &s)
    {
        copy(s.data.begin(), s.data.end(), back_inserter(data));
        return *this;
    }
    size_type size() { return data.size(); }
    size_type size() const { return data.size(); }

    // char*()
    operator char *();
    operator char *() const;

private:
    Vec<char> data;
};

// I/O
// cout <<
ostream &operator<<(ostream &os, const Str &s)
{
    for (decltype(s.size()) i = 0; i != s.size(); ++i)
        os << s[i]; // 需要#include <iostream>
    return os;
}
// cin >>
istream &operator>>(istream &is, Str &s)
{
    // obliterate existing value(s)
    s.data.clear();
    // read and discard leading whitespace
    char c;
    while (is.get(c) && isspace(c))
        ; // nothing to do, except testing the condition
    // if still something to read, do so until next whitespace character
    if (is)
    {
        do
            s.data.push_back(c); // compile error!, data is private
        while (is.get(c) && !isspace(c));
        // if we read whitespace, then put it back on the stream
        if (is)
            is.unget();
    }
    return is;
}

// +
Str operator+(const Str &s, const Str &t)
{
    Str r = s; // assignment
    r += t;    // operator+=
    return r;  // return copy
}

void demo_c_str()
{

    string s = "abcdefg";
    auto cstr = s.c_str();
    auto no_end_cstr = s.data();
    auto sz = s.size();
    char *buffer = new char[sz + 1]; // malloc
    copy_n(s.begin(), sz, buffer);
    buffer[sz] = '\0';
    cout << "buffer: " << buffer << endl;
    delete[] buffer; // free
}

int main(int argc, char **argv)
{

    Str s = "hello";
    s = "aaa";
    s += "123123";

    Vec<int> v(5, 2);
    auto sz = size_t(v); // type conversion operator
    cout << "size of v: " << sz << endl;
    demo_c_str();
    return 0;
}