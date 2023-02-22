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

// END class Ptr

class Picture; // 提前声明  forward declaration

// private classes for use in the implementation only
class Pic_base
{

    friend std::ostream &operator<<(std::ostream &, const Picture &);
    // 子类做friend class
    friend class Frame_Pic;
    friend class HCat_Pic;
    friend class VCat_Pic;
    friend class String_Pic;

    // no public
    typedef vector<string>::size_type ht_sz;
    typedef string::size_type wd_sz;

    virtual wd_sz width() const = 0; // 纯虚函数，这个类是abstract base class，不能被实例化
    virtual ht_sz height() const = 0;
    virtual void display(ostream &, ht_sz, bool) const = 0;

protected:
    // 填充空格
    static void pad(std::ostream &os, wd_sz beg, wd_sz end)
    {
        while (beg != end)
        {
            os << " ";
            ++beg;
        }
    }
};

class String_Pic : public Pic_base
{
    std::vector<std::string> data;
    String_Pic(const std::vector<std::string> &v) : data(v) {}
    wd_sz width() const;
    ht_sz height() const { return data.size(); }
    void display(std::ostream &, ht_sz, bool) const;
};

Pic_base::wd_sz String_Pic::width() const
{
    Pic_base::wd_sz n = 0;
    for (Pic_base::ht_sz i = 0; i != data.size(); ++i)
        n = max(n, data[i].size());
    return n;
}

void String_Pic::display(ostream &os, ht_sz row, bool do_pad) const
{
    wd_sz start = 0;
    // write the row if we're still in range
    if (row < height())
    {
        os << data[row];
        start = data[row].size();
    }
    // pad the output if necessary
    if (do_pad)
        pad(os, start, width());
}

class Frame_Pic : public Pic_base
{
    friend Picture frame(const Picture &);
    Ptr<Pic_base> p;
    Frame_Pic(const Ptr<Pic_base> &pic) : p(pic) {}
    wd_sz width() const { return p->width() + 4; }
    ht_sz height() const { return p->height() + 4; }
    void display(std::ostream &, ht_sz, bool) const;
};
void Frame_Pic::display(ostream &os, ht_sz row, bool do_pad) const
{
    if (row >= height())
    {
        // out of range
        if (do_pad)
            pad(os, 0, width());
    }
    else
    {
        if (row == 0 || row == height() - 1)
        {
            // top or bottom row
            os << string(width(), '*');
        }
        else if (row == 1 || row == height() - 2)
        {
            // second from top or bottom row
            os << "*";
            pad(os, 1, width() - 1);
            os << "*";
        }
        else
        {
            // interior row
            os << "* ";
            p->display(os, row - 2, true);
            os << " *";
        }
    }
}
class VCat_Pic : public Pic_base
{
    friend Picture vcat(const Picture &, const Picture &);
    Ptr<Pic_base> top, bottom;
    VCat_Pic(const Ptr<Pic_base> &t, const Ptr<Pic_base> &b) : top(t), bottom(b) {}
    wd_sz width() const
    {
        return std::max(top->width(), bottom->width());
    }
    ht_sz height() const
    {
        return top->height() + bottom->height();
    }
    void display(std::ostream &, ht_sz, bool) const;
};

void VCat_Pic::display(ostream &os, ht_sz row, bool do_pad) const
{
    wd_sz w = 0;
    if (row < top->height())
    {
        // we are in the top subpicture
        top->display(os, row, do_pad);
        w = top->width();
    }
    else if (row < height())
    {
        // we are in the bottom subpicture
        bottom->display(os, row - top->height(), do_pad);
        w = bottom->width();
    }
    if (do_pad)
        pad(os, w, width());
}

class HCat_Pic : public Pic_base
{
    friend Picture hcat(const Picture &, const Picture &);
    Ptr<Pic_base> left, right;
    HCat_Pic(const Ptr<Pic_base> &l, const Ptr<Pic_base> &r) : left(l), right(r) {}
    wd_sz width() const { return left->width() + right->width(); }
    ht_sz height() const
    {
        return std::max(left->height(), right->height());
    }
    void display(std::ostream &, ht_sz, bool) const;
};

void HCat_Pic::display(ostream &os, ht_sz row, bool do_pad) const
{
    left->display(os, row, do_pad || row < right->height());
    right->display(os, row, do_pad);
}

// public interface class and operations
class Picture
{
    friend Picture frame(const Picture &pic);
    friend Picture hcat(const Picture &, const Picture &);
    friend Picture vcat(const Picture &, const Picture &);
    friend std::ostream &operator<<(std::ostream &os, const Picture &picture);

public:
    Picture(const std::vector<std::string> & =
                std::vector<std::string>());
    Picture(Pic_base *ptr) : p(ptr) {}

private:
    Ptr<Pic_base> p;
};

Picture frame(const Picture &pic)
{
    Pic_base *ret = new Frame_Pic(pic.p);
}
Picture hcat(const Picture &l, const Picture &r)
{

    return new HCat_Pic(l.p, r.p);
}
Picture vcat(const Picture &, const Picture &)
{
}
std::ostream &operator<<(std::ostream &os, const Picture &picture)
{
    const Pic_base::ht_sz ht = picture.p->height();
    for (Pic_base::ht_sz i = 0; i != ht; ++i)
    {
        picture.p->display(os, i, false);
        os << endl;
    }
    return os;
}
void demo_picture()
{
}

int main(int argc, char **argv)
{
    demo_picture();
    return 0;
}