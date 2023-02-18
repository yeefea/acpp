
#include <string>
#include <memory>
#include "Student_info.h"
/*
template classes
抽象数据类型
vector
list
map
unordered_map
...
*/

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
        unchecked_append();
    }

    // 迭代器
    iterator begin() { return data; }
    const_iterator begin() const { return data; } // const 重载

    iterator end() { return limit; }
    const_iterator end() const { return limit; } // const 重载

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

void demo_vec()
{
    Vec<Student_info> vs;

    Vec<double> vi(100, 3);
    describe_vec(vi);
}

int main(int argc, char **argv)
{
    demo_vec();
    return 0;
}