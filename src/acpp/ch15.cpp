#include <vector>
#include <iostream>

using namespace std;

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

class Picture;

// private classes for use in the implementation only
class Pic_base
{
    friend std::ostream &operator<<(std::ostream &, const Picture &);
    friend class Frame_Pic;
    friend class HCat_Pic;
    friend class VCat_Pic;
    friend class String_Pic;

    // no public
    typedef vector<string>::size_type ht_sz;
    typedef string::size_type wd_sz;

    virtual wd_sz width() const = 0;
    virtual ht_sz height() const = 0;
    virtual void display(ostream &, ht_sz, bool) const = 0;
};

class String_Pic : public Pic_base
{
    std::vector<std::string> data;
    String_Pic(const std::vector<std::string> &v) : data(v) {}
    wd_sz width() const;
    ht_sz height() const;
    void display(std::ostream &, ht_sz, bool) const;
};
class Frame_Pic : public Pic_base
{
    Ptr<Pic_base> p;
    Frame_Pic(const Ptr<Pic_base> &pic) : p(pic) {}
    wd_sz width() const;
    ht_sz height() const;
    void display(ostream &, ht_sz, bool) const;
};
class VCat_Pic : public Pic_base
{
    Ptr<Pic_base> top, bottom;
    VCat_Pic(const Ptr<Pic_base> &t, const Ptr<Pic_base> &b) : top(t), bottom(b) {}
    wd_sz width() const;
    ht_sz height() const;
    void display(std::ostream &, ht_sz, bool) const;
};
class HCat_Pic : public Pic_base
{
    Ptr<Pic_base> left, right;
    HCat_Pic(const Ptr<Pic_base> &l, const Ptr<Pic_base> &r) : left(l), right(r) {}
    wd_sz width() const;
    ht_sz height() const;
    void display(std::ostream &, ht_sz, bool) const;
};
// public interface class and operations
class Picture
{
public:
    Picture(const std::vector<std::string> & =
                std::vector<std::string>());

private:
    Ptr<Pic_base> p;
};

void demo_picture()
{
}

int main(int argc, char **argv)
{
    demo_picture();
    return 0;
}