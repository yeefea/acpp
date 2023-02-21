#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include "grade.h"

using namespace std;

template <typename T>
class Ptr;

istream &read_hw(istream &in, vector<double> &hw)
{
    if (in)
    {
        // get rid of previous contents
        hw.clear();
        // read homework grades
        double x;
        while (in >> x)
            hw.push_back(x);
        // clear the stream so that input will work for the next student
        in.clear();
    }
    return in;
}

class Core
{

public:
    virtual double grade() const; // 虚函数，用于多态、动态绑定
    // double grade() const;  这样无法支持多态，一定要virtual
    virtual istream &read(istream &);
    Core() : midterm(0), final(0){};
    Core(istream &is) { read(is); };
    string name() const;
    void set_name(string n) { Core::n = n; };
    vector<double> homework;
    virtual ~Core() { cout << n << " call virtual destructor." << endl; } // virtual destructor
    // class Grad 继承了class Core的虚析构函数
    virtual Core *clone() const { return new Core(*this); }
    virtual void regrade(double d1, double d2 = 0) { final = d1; }

protected:
    istream &read_common(istream &);
    double midterm;
    double final;

private:
    string n;
};

string Core::name() const { return n; }

double Core::grade() const
{
    // cout << "Core grade" << endl;
    return ::grade(midterm, final, homework);
}

istream &Core::read_common(istream &in)
{
    in >> n >> midterm >> final;
    return in;
}

istream &Core::read(istream &in)
{
    cout << "read() " << endl;
    read_common(in);
    read_hw(in, homework);
    return in;
}

// Grad representes a graduate student
class Grad : public Core // public derived class
{
    /*
    继承除了构造函数、析构函数、赋值运算以外的成员
    */

public:
    Grad() : thesis(0){};            // 会隐式调用Core()
    Grad(istream &is) { read(is); }; // 会隐式调用Core()
    double grade() const;
    istream &read(istream &);
    void regrade(double d1, double d2 = 0); // override

protected:
    Grad *clone() const { return new Grad(*this); }

private:
    double thesis;
};

istream &Grad::read(istream &in)
{
    read_common(in);
    in >> thesis;
    read_hw(in, homework);
    // read_hw(in, Core::homework); 用Core::homework也可以，Core::类似于python的super
    return in;
}

double Grad::grade() const
{
    // cout << "Grad grade" << endl;
    return min(Core::grade(), thesis); // Core::类似于python的super
}

void Grad::regrade(double d1, double d2)
{
    final = d1;
    thesis = d2;
}

bool compare(const Core &c1, const Core &c2)
{
    return c1.name() < c2.name();
}

bool compare_grades(const Core &c1, const Core &c2)
{
    return c1.grade() < c2.grade();
}

// Handle 泛型handle class
template <typename T>
class Handle
{
public:
    // constructors
    Handle() : p(nullptr) { cout << "constructor ()" << endl; }
    Handle(const Handle &s) : p(nullptr)
    {
        cout << "copy constructor, obj = " << s->name() << endl;
        if (s.p)
            p = s.p->clone(); // 类型T需要有clone()函数
    }
    Handle(T *t) : p(t) {}
    Handle &operator=(const Handle &);
    ~Handle() { delete p; }

    operator bool() const { return p; }
    T &operator*() const;
    T *operator->() const; // 原始的->运算符左边是指针，右边是成员名。这里重载，返回T类型的指针

private:
    T *p;
};

template <class T>
Handle<T> &Handle<T>::operator=(const Handle &rhs)
{
    cout << "assignment operator, new name = " << rhs->name() << endl;
    if (&rhs != this)
    {
        delete p;
        p = rhs.p ? rhs.p->clone() : nullptr;
    }
    return *this;
}

template <class T>
T &Handle<T>::operator*() const // 解引用运算符*
{
    if (p)
        return *p;
    throw runtime_error("unbound Handle");
}

template <class T>
T *Handle<T>::operator->() const // ->运算符
{
    if (p)
        return p;
    throw runtime_error("unbound Handle");
}

bool compare_Core_handles(const Handle<Core> cp1, const Handle<Core> cp2)
{
    cout << "call compare_Core_handles on " << cp1->name() << " and " << cp2->name() << endl;
    return compare(*cp1, *cp2);
}

// 引用计数handle
template <typename T>
class Ref_handle
{

public:
    Ref_handle() : refptr(new size_t(1)), p(0) {}
    Ref_handle(T *t) : refptr(new size_t(1)), p(t) {}
    Ref_handle(const Ref_handle &h) : refptr(h.refptr), p(h.p) // copy constructor
    {
        ++(*refptr); // refcnt++
    }
    Ref_handle &operator=(const Ref_handle &); // assignment operator
    ~Ref_handle();

    operator bool() const { return p; }
    T &operator*() const
    {
        if (p)
        {
            return *p;
        }
        throw runtime_error("unbound Ref_handle");
    }

    T *operator->() const
    {
        if (p)
        {
            return p;
        }
        throw runtime_error("unbound Ref_handle2");
    }

private:
    T *p;           // 指向对象的指针
    size_t *refptr; // 引用计数
};

template <typename T>
Ref_handle<T> &Ref_handle<T>::operator=(const Ref_handle &rhs)
{
    ++(rhs).refptr; // ++refcnt
    if (--(*refptr) == 0)
    {
        delete refptr;
        delete p;
    }
    refptr = rhs.refptr;
    p = rhs.p;
    return *this;
}

template <typename T>
Ref_handle<T>::~Ref_handle()
{
    if (--(*refptr) == 0)
    {
        delete refptr;
        delete p;
    }
}

// 简陋版智能指针
template <typename T>
class Ptr
{
public:
    void make_unique()
    {
        // 克隆对象，不再和其他指针共享
        if (*refptr != 1)
        {
            --*refptr;
            refptr = new size_t(1);
            p = p ? clone(p) : 0;
        }
    }

    Ptr() : refptr(new size_t(1)), p(0) {}
    Ptr(T *t) : refptr(new size_t(1)), p(t) {}
    Ptr(const Ptr &h) : refptr(h.refptr), p(h.p) { ++*refptr; }

    Ptr &operator=(const Ptr &);
    ~Ptr();

    operator bool() const { return p; }
    T &operator*() const;
    T *operator->() const;

private:
    T *p;
    size_t *refptr;
};

template <typename T>
Ptr<T> &Ptr<T>::operator=(const Ptr<T> &rhs)
{

    ++(*rhs.refptr);
    if (--*refptr == 0)
    {
        delete refptr;
        delete p;
    }

    refptr = rhs.refptr;
    p = rhs.p;
    return *this;
}

template <typename T>
Ptr<T>::~Ptr<T>()
{
    if (--*refptr == 0)
    {
        delete refptr;
        delete p;
    }
}

template <typename T>
T &Ptr<T>::operator*() const
{
    if (*refptr > 0)
    {
        return *p;
    }
    throw runtime_error("unbound Ptr");
}
template <typename T>
T *Ptr<T>::operator->() const
{
    if (*refptr > 0)
    {
        return p;
    }
    throw runtime_error("unbound Ptr2");
}

class New_Student_info
{

public:
    New_Student_info() {}
    New_Student_info(istream &is) { read(is); }
    istream &read(istream &);
    string name() const
    {
        if (cp)
        {
            return cp->name();
        }
        throw runtime_error("uninitialized Student");
    }
    static bool compare(const New_Student_info &s1, const New_Student_info &s2)
    {
        return s1.name() < s2.name();
    }
    void regrade(double final, double thesis);

private:
    Ptr<Core> cp;
};

void New_Student_info::regrade(double final, double thesis)
{
    cp.make_unique();
    if (cp)
    {
        cp->regrade(final, thesis);
    }
    else
    {
        throw runtime_error("regrade of unknown student");
    }
}

istream &New_Student_info::read(istream &is)
{
    char ch;
    is >> ch;
    if (ch == 'U')
    {
        cp = new Core(is);
    }
    else
    {
        cp = new Grad(is);
    }
    return is;
}

void demo_handle()
{
    vector<Handle<Core>> students;

    stringstream sstream("U yeefea 10 11 12 13 14 15 16\nG geefea 99 98 97 96 95 94");

    Handle<Core> record;
    // record->set_name("aaa");
    char ch;

    string::size_type maxlen = 0;
    while (sstream >> ch)
    {
        if (ch == 'U')
            record = new Core; // allocate a Core object
        else
            record = new Grad;                       // allocate a Grad object
        record->read(sstream);                       // Handle<T>::->, then virtual call to read
        maxlen = max(maxlen, record->name().size()); // Handle<T>::->
        students.push_back(record);
    }

    sort(students.begin(), students.end(), compare_Core_handles);
    // write the names and grades
    for (decltype(students.size()) i = 0;
         i != students.size(); ++i)
    {
        // students[i] is a Handle, which we dereference to call the functions
        cout << students[i]->name()
             << string(maxlen + 1 - students[i]->name().size(), ' ');
        try
        {
            double final_grade = students[i]->grade();
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec) << endl;
        }
        catch (domain_error e)
        {
            cout << e.what() << endl;
        }
        // no delete statement
    }
}

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
// clone 辅助函数
template <class T>
T *clone(const T *tp)
{
    return tp->clone();
}

// 模板具体化
template <>
Vec<char> *clone(const Vec<char> *vp)
{
    return new Vec<char>(*vp);
}

class Str
{
    friend std::istream &operator>>(std::istream &, Str &);

public:
    Str &operator+=(const Str &s)
    {
        data.make_unique();
        std::copy(s.data->begin(), s.data->end(),
                  std::back_inserter(*data));
        return *this;
    }
    // interface as before
    typedef Vec<char>::size_type size_type;
    // reimplement constructors to create Ptrs
    Str() : data(new Vec<char>) {}
    Str(const char *cp) : data(new Vec<char>)
    {
        std::copy(cp, cp + std::strlen(cp),
                  std::back_inserter(*data));
    }
    Str(size_type n, char c) : data(new Vec<char>(n, c)) {}
    template <class In>
    Str(In i, In j) : data(new Vec<char>)
    {
        std::copy(i, j, std::back_inserter(*data));
    }
    // call make_unique as necessary，因为调用者可能会修改返回char&
    char &operator[](size_type i)
    {
        data.make_unique();
        return (*data)[i];
    }
    const char &operator[](size_type i) const { return (*data)[i]; }
    size_type size() const { return data->size(); }

private:
    Ptr<Vec<char>> data;
};

ostream &operator<<(ostream &os, const Str &s)
{
    for (decltype(s.size()) i = 0; i != s.size(); ++i)
        os << s[i]; // 需要#include <iostream>
    return os;
}
Str operator+(const Str &s, const Str &t)
{
    Str r = s; // assignment
    r += t;    // operator+=
    return r;  // return copy
}

void demo_str()
{
    Str s1("123123");
    Str s2 = s1 + "456";
    cout << s2 << endl;
}
int main(int argc, char **argv)
{
    demo_handle();

    demo_str();

    return 0;
}
