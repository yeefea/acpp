#include <list>
#include <string>
#include <cctype>
#include "Student_info.h"
#include "grade.h"
#include "util.h"

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::string;
using std::vector;

vector<Student_info> extract_fails1(vector<Student_info> &students)
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
    Student_info tmp = Student_info{"one", 1, 2};
    tmp.homework.push_back(3);
    tmp.homework.push_back(4);
    tmp.homework.push_back(5);
    students.push_back(tmp);

    tmp = Student_info{"two", 99, 98};
    tmp.homework.push_back(97);
    tmp.homework.push_back(96);
    tmp.homework.push_back(95);
    students.push_back(tmp);

    auto res = extract_fails1(students);

    for (auto it = res.begin(); it != res.end(); it++)
    {
        cout << it->name << " failed, grade = " << grade(*it) << endl;
    }
}

vector<Student_info> extract_fails2(vector<Student_info> &students)
{
    vector<Student_info> fail;
    vector<Student_info>::size_type i = 0;
    while (i != students.size())
    {
        if (fgrade(students[i]))
        {
            fail.push_back(students[i]);
            students.erase(students.begin() + i);
        }
        else
        {
            ++i;
        }
    }
    return fail;
}

void demo2()
{
    vector<Student_info> students;
    Student_info tmp = Student_info{"one", 1, 2};
    tmp.homework.push_back(3);
    tmp.homework.push_back(4);
    tmp.homework.push_back(5);
    students.push_back(tmp);

    tmp = Student_info{"two", 99, 98};
    tmp.homework.push_back(97);
    tmp.homework.push_back(96);
    tmp.homework.push_back(95);
    students.push_back(tmp);

    auto res = extract_fails2(students);

    for (auto it = students.begin(); it != students.end(); it++)
    {
        cout << it->name << " passed, grade = " << grade(*it) << endl;
    }

    for (auto it = res.begin(); it != res.end(); it++)
    {
        cout << it->name << " failed, grade = " << grade(*it) << endl;
    }
}

void demo_iterators()
{
    vector<Student_info> students;
    Student_info tmp = Student_info{"one", 1, 2};
    tmp.homework.push_back(3);
    tmp.homework.push_back(4);
    tmp.homework.push_back(5);
    students.push_back(tmp);

    tmp = Student_info{"two", 99, 98};
    tmp.homework.push_back(97);
    tmp.homework.push_back(96);
    tmp.homework.push_back(95);
    students.push_back(tmp);

    for (vector<Student_info>::iterator it = students.begin(); it != students.end(); ++it)
    {
        cout << "student" << it->name << ", grade = " << grade(*it) << endl;
    }
    // const iterator
    // 这里隐式转换，把iterator转为const_iterator，但是const_iterator不能转成iterator
    for (vector<Student_info>::const_iterator it = students.begin(); it != students.end(); ++it)
    {
        cout << "student" << it->name << ", grade = " << grade(*it) << endl;
    }
}

vector<Student_info> extract_fails3(vector<Student_info> &students)
{
    vector<Student_info> fail;
    vector<Student_info>::iterator iter = students.begin();
    while (iter != students.end())
    {
        if (fgrade(*iter))
        {
            fail.push_back(*iter);
            iter = students.erase(iter); // 注意这里很关键！！！！！
        }
        else
        {
            ++iter;
        }
    }
    return fail;
}

void demo3()
{
    vector<Student_info> students;
    Student_info tmp = Student_info{"one", 1, 2};
    tmp.homework.push_back(3);
    tmp.homework.push_back(4);
    tmp.homework.push_back(5);
    students.push_back(tmp);

    tmp = Student_info{"two", 99, 98};
    tmp.homework.push_back(97);
    tmp.homework.push_back(96);
    tmp.homework.push_back(95);
    students.push_back(tmp);

    auto res = extract_fails3(students);

    for (auto it = students.begin(); it != students.end(); it++)
    {
        cout << it->name << " passed, grade = " << grade(*it) << endl;
    }

    for (auto it = res.begin(); it != res.end(); it++)
    {
        cout << it->name << " failed, grade = " << grade(*it) << endl;
    }
}

list<Student_info> extract_fails4(list<Student_info> &students)
{
    list<Student_info> fail;
    list<Student_info>::iterator iter = students.begin();
    while (iter != students.end())
    {
        if (fgrade(*iter))
        {
            fail.push_back(*iter);
            iter = students.erase(iter); // 注意这里很关键！！！！！
        }
        else
        {
            ++iter;
        }
    }
    return fail;
}

// demo4 linked list
void demo4()
{
    list<Student_info> students;
    Student_info tmp = Student_info{"one", 1, 2};
    tmp.homework.push_back(3);
    tmp.homework.push_back(4);
    tmp.homework.push_back(5);
    students.push_back(tmp);

    tmp = Student_info{"two", 99, 98};
    tmp.homework.push_back(97);
    tmp.homework.push_back(96);
    tmp.homework.push_back(95);
    students.push_back(tmp);

    auto res = extract_fails4(students);

    for (auto it = students.begin(); it != students.end(); it++)
    {
        cout << it->name << " passed, grade = " << grade(*it) << endl;
    }

    for (auto it = res.begin(); it != res.end(); it++)
    {
        cout << it->name << " failed, grade = " << grade(*it) << endl;
    }
    students.sort(compare); // list 有自己的sort函数
}

vector<string> split(const string &s)
{

    vector<string> ret;
    typedef string::size_type str_size;
    str_size i = 0;

    while (i != s.size())
    {

        while (i != s.size() && isspace(s[i])) // include cctype
        {
            ++i;
        }
        str_size j = i;
        while (j != s.size() && !isspace(s[j]))
        {
            ++j;
        }
        if (i != j)
        {
            ret.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return ret;
}

void demo_string()
{

    string s;

    while (getline(cin, s)) // getline
    {
        vector<string> sp = split(s);
        for (auto iter = sp.cbegin(); iter != sp.cend(); ++iter)
        {
            cout << *iter << endl;
        }
    }
}

void demo_vector_concatenate()
{

    vector<string> vec(5, "123");
    vector<string> vec2(5, "456");
    cout << string(20, '=') << endl;
    describe_string_vector(vec);
    cout << string(20, '=') << endl;
    describe_string_vector(vec2);
    cout << string(20, '=') << endl;
    // append
    vec.insert(vec.end(), vec2.begin(), vec2.end());

    describe_string_vector(vec);
    cout << string(20, '=') << endl;
}

int main()
{
    // demo1();
    // demo2();
    // demo_iterators();
    // demo3();
    // demo4(); // linked list
    // demo_string();
    demo_vector_concatenate();
    return 0;
}
