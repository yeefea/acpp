
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
    explicit Vec(size_type n, const T &val = T()){create(n, val)}
    // copy constructor
    Vec(const Vec &v)
    {
        create(v.begin(), v.end());
    }
    ~Vec() { uncreate(); }  // destructor

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

    void push_back(&const T& val){
        if (avail == limit){
            grow();
        }
        unchecked_append();
    }

    // 迭代器
    iterator begin() { return data; }
    const_iterator begin() const { return data; } // const 重载

    iterator end() { return limit; }
    const_iterator end() const { return limit; } // const 重载

private:            // implementation
    iterator data;  // begin
    iterator avail;
    iterator limit; // end
};

void demo_vec()
{
    Vec<Student_info> vs;
    Vec<double> vi(100);
}

int main(int argc, char **argv)
{
    demo_vec();
    return 0;
}