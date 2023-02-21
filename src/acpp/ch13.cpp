#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include "grade.h"
using namespace std;

class New_Student_info;

class Core
{
    friend class New_Student_info; // friend类

public:
    virtual double grade() const; // 虚函数，用于多态、动态绑定
    // double grade() const;  这样无法支持多态，一定要virtual
    virtual istream &read(istream &);
    Core() : midterm(0), final(0){};
    Core(istream &is) { read(is); };
    string name() const;
    void set_name(string n) { Core::n = n; };
    vector<double> homework;
    virtual ~Core() { cout << "call virtual destructor." << endl; } // virtual destructor
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
    cout << "calling grade() from Core" << endl;
    return ::grade(midterm, final, homework);
}

istream &Core::read_common(istream &in)
{
    in >> n >> midterm >> final;
    return in;
}

istream &Core::read(istream &in)
{
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
    cout << "calling grade() from Grad" << endl;
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
bool compare_Core_ptrs(const Core *cp1, const Core *cp2)
{
    cout << "call compare_Core_ptrs on " << cp1->name() << " and " << cp2->name() << endl;
    return compare(*cp1, *cp2);
}
void demo_inheritance()
{
}

void demo_dynamic_binding()
{
    Core c;
    Grad g;
    for (int i = 1; i <= 10; i++)
    {
        c.homework.push_back(i);
        g.homework.push_back(i * 2);
    }
    Core *p = nullptr;
    Core &r = g;
    cout << "c statically bound to Core" << endl;
    c.grade(); // statically bound to Core::grade()
    cout << "g statically bound to Grad" << endl;
    g.grade(); // statically bound to Grad::grade()
    cout << "p dynamically bound to Core" << endl;
    p = &c;
    p->grade(); // dynamically bound, depending on the type of the object to which p points
    cout << "p dynamically bound to Grad" << endl;
    p = &g;
    p->grade(); // dynamically bound, depending on the type of the object to which p points
    cout << "r dynamically bound to Grad" << endl;
    r.grade(); // dynamically bound, depending on the type of the object to which r refers
}

void demo_polymorphism()
{
    // Grad g(cin);    // read a Grad record
    // Grad g2(cin);   // read a Grad record
    // Core c(cin);    // read a Core record
    // Core c2(cin);   // read a Core record
    Grad g, g2;
    g.set_name("g");
    g.homework.push_back(98);
    g.homework.push_back(96);
    g.homework.push_back(91);
    g2.set_name("g2");
    g2.homework.push_back(91);
    g2.homework.push_back(93);
    g2.homework.push_back(90);
    Core c, c2;
    c.set_name("c");
    c.homework.push_back(81);
    c.homework.push_back(86);
    c.homework.push_back(81);
    c2.set_name("c2");
    c2.homework.push_back(8);
    c2.homework.push_back(6);
    c2.homework.push_back(1);

    bool res;
    res = compare(g, g2); // compare two Grad records
    cout << "compare result: " << res << endl;
    res = compare(c, c2); // compare two Core records
    cout << "compare result: " << res << endl;
    res = compare(g, c); // compare Grad record with a Core record
    cout << "compare result: " << res << endl;

    res = compare_grades(g, g2); // compare two Grad records
    cout << "compare_grades result: " << res << endl;
    res = compare_grades(c, c2); // compare two Core records
    cout << "compare_grades result: " << res << endl;
    res = compare_grades(g, c); // compare Grad record with a Core record
    cout << "compare_grades result: " << res << endl;
}

void demo_polimorphism2()
{
    // 用指针实现动态绑定
    vector<Core *> students; // store pointers, not objects
    Core *record;            // temporary must be a pointer as well
    char ch;
    string::size_type maxlen = 0;
    string text = "U yeefea 1 2 3 4 5 6 7 G gyeefea 90 91 92 93 94 95 96";
    stringstream sstream(text);
    // read and store the data
    while (sstream >> ch)
    {
        if (ch == 'U')
            record = new Core; // allocate a Core object
        else
            record = new Grad;                       // allocate a Grad object
        record->read(sstream);                       // virtual call
        maxlen = max(maxlen, record->name().size()); // dereference
        students.push_back(record);
    }
    // pass the version of compare that works on pointers
    sort(students.begin(), students.end(), compare_Core_ptrs);
    // write the names and grades
    for (vector<Core *>::size_type i = 0;
         i != students.size(); ++i)
    {
        // students[i] is a pointer that we dereference to call the functions
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
        delete students[i]; // free the object allocated when reading
    }
}

// Student_info handle class多态类型的包装器
class New_Student_info
{
public:
    // constructors and copy control
    New_Student_info() : cp(0) {}
    New_Student_info(std::istream &is) : cp(0) { read(is); }

    New_Student_info(const New_Student_info &);
    New_Student_info &operator=(const New_Student_info &);
    ~New_Student_info() { delete cp; }
    // operations
    std::istream &read(std::istream &);
    std::string name() const
    {
        if (cp)
            return cp->name();
        else
            throw std::runtime_error("uninitialized Student");
    }
    double grade() const
    {
        if (cp)
            return cp->grade(); // 调用虚函数
        else
            throw std::runtime_error("uninitialized Student");
    }
    static bool compare(const New_Student_info &s1,
                        const New_Student_info &s2) // static 类函数，和java一样
    {
        return s1.name() < s2.name();
    }

private:
    Core *cp;
};

istream &New_Student_info::read(istream &is)
{
    // 注意下面这行
    delete cp; // delete previous object, if any
    char ch;
    is >> ch; // get record type
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
New_Student_info::New_Student_info(const New_Student_info &s) : cp(0)
{
    if (s.cp)
        cp = s.cp->clone(); // Core和Grad需要实现clone函数
}
New_Student_info &New_Student_info::operator=(const New_Student_info &s)
{
    if (&s != this)
    {
        delete cp;
        if (s.cp)
            cp = s.cp->clone(); // Core和Grad需要实现clone函数
        else
            cp = 0;
    }
    return *this;
}

void demo_handle_class()
{
    vector<New_Student_info> students;
    New_Student_info record;
    string::size_type maxlen = 0;
    // read and store the data
    string text = "U yeefea 10 11 12 13 14 15 G david 98 99 100 99 97 95";
    stringstream sstream(text);

    while (record.read(sstream))
    {
        maxlen = max(maxlen, record.name().size());
        students.push_back(record);
    }
    // alphabetize the student records
    sort(students.begin(), students.end(), New_Student_info::compare);
    // write the names and grades
    for (vector<New_Student_info>::size_type i = 0;
         i != students.size(); ++i)
    {
        cout << students[i].name()
             << string(maxlen + 1 - students[i].name().size(), ' ');
        try
        {
            double final_grade = students[i].grade();
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec) << endl;
        }
        catch (domain_error e)
        {
            cout << e.what() << endl;
        }
    }
}

void demo_subtileties()
{

    // 1
    vector<Core> students;
    string text = "yeefeag 123 345 123 123 123";
    stringstream sstream(text);
    Grad g(sstream);

    students.push_back(g); // 只有g里Core的那部分被拷贝到了vector里

    // 2

    Core cc;
    Grad gg(g);
    Core *cp;
    cp = &cc;
    cp->regrade(10, 100);

    cp = &gg;
    cp->regrade(11, 101);

    cout << cp->name() << " " << endl;
}
int main(int argc, char **argv)
{
    demo_dynamic_binding();
    demo_polymorphism();
    demo_polimorphism2();
    demo_handle_class();
    demo_subtileties();
    return 0;
}