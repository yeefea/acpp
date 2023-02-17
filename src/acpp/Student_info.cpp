#include "Student_info.h"
#include "grade.h"

using std::istream;
using std::string;
using std::vector;

bool Student_info::valid() const { return !homework.empty(); }

istream &Student_info::read(istream &in)
{
    in >> name >> midterm >> final;
    read_hw(in, homework);
    return in;
}

double Student_info::grade() const
{
    // ::表示非成员函数
    return ::grade(midterm, final, homework);
}

string Student_info::get_name() const
{
    return n;
}

bool compare(const Student_info &x, const Student_info &y)
{
    return x.get_name() < y.get_name();
}
istream &read(istream &is, Student_info &s)
{
    // read and store the student's name and midterm and final exam grades
    is >> s.name >> s.midterm >> s.final;
    read_hw(is, s.homework); // read and store all the student's homework grades
    return is;
}
// read homework grades from an input stream into a `vector'
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
