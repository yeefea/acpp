#include <string>
#include <iostream>
#include "Student_info.h"
#include "grade.h"

using std::istream;
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