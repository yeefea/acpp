#include "Student_info.h"
#include "grade.h"

using std::vector;
using std::cout;
using std::endl;

bool fgrade(const Student_info &s)
{
    return grade(s) < 60;
}

vector<Student_info> extract_fails(vector<Student_info> &students)
{
    vector<Student_info> pass, fail;

    for (vector<Student_info>::size_type i = 0; i != students.size(); ++i)
    {
        if (fgrade(students[i]))
        {
            fail.push_back(students[i]);
        }
        else
        {
            pass.push_back(students[i]);
        }
    }
    return fail;
}

void demo1()
{

    vector<Student_info> students;
    Student_info tmp = Student_info{"one",1,2};
    tmp.homework.push_back(3);
    tmp.homework.push_back(4);
    tmp.homework.push_back(5);
    students.push_back(tmp);

    tmp = Student_info{"two",99, 98};
    tmp.homework.push_back(97);
    tmp.homework.push_back(96);
    tmp.homework.push_back(95);
    students.push_back(tmp);

    auto res = extract_fails(students);

    for (auto it = res.begin(); it!= res.end(); it++){
        cout << it->name << " failed, grade = " << grade(*it) << endl;
    }
}

int main()
{
    demo1();
    return 0;
}