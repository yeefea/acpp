#include <vector>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "median.h"
#include "Student_info.h"
#include "grade.h"

using std::cin;
using std::cout;
using std::domain_error;
using std::endl;
using std::istream;
using std::max;
using std::setprecision;
using std::sort;
using std::streamsize;
using std::string;
using std::vector;

void demo_function1()
{

    double g = grade(1.0, 2.0, 3.0);
    vector<double> vec;
    for (int i = 0; i < 10; i++)
    {
        vec.push_back(double(i));
    }

    double m = median(vec);

    auto prec = cout.precision(1);
    cout << "grade: " << g << ", median: " << m << setprecision(prec) << endl;
}

void demo_const()
{

    vector<double> homework;
    vector<double> &hw = homework; // homework的引用
    vector<double> &hw1 = hw;      // 依然是homework的引用，而不是hw的引用
    for (int i = 0; i < hw1.size(); i++)
    {
        cout << hw1[i] << " ";
    }
    const vector<double> &chw = homework; // const reference
    const vector<double> &chw1 = chw;     // const reference to homework

    for (int i = 0; i < chw1.size(); i++)
    {
        cout << chw1[i] << " ";
    }
    cout << endl;
}

void demo_functions()
{

    cout << "enter your first name: ";
    string name;
    cin >> name;
    cout << "Hello, " << name << "!" << endl;
    cout << "please enter your midterm and final exam grades: ";
    double midterm, final;
    cin >> midterm >> final;

    cout << "Enter all your homework grades, "
            "followed by end-of-file: ";

    vector<double> homework;
    // read the homework grades
    read_hw(cin, homework);
    // compute and generate the final grade, if possible
    try
    {
        double final_grade = grade(midterm, final, homework);
        streamsize prec = cout.precision();
        cout << "Your final grade is " << setprecision(3)
             << final_grade << setprecision(prec) << endl;
    }
    catch (domain_error)
    {
        cout << endl
             << "You must enter your grades. "
                "Please try again."
             << endl;
    }
}

void demo_student()
{
    vector<Student_info> students;
    Student_info record;
    string::size_type maxlen = 0;
    // read and store all the records, and find the length of the longest name
    while (read(cin, record))
    {
        cout << "student name: " << record.name << endl;
        maxlen = max(maxlen, record.name.size());
        students.push_back(record);
    }
    // alphabetize the records
    sort(students.begin(), students.end(), compare);
    for (vector<Student_info>::size_type i = 0;
         i != students.size(); ++i)
    {
        // write the name, padded on the right to maxlen + 1 characters
        cout << students[i].name
             << string(maxlen + 1 - students[i].name.size(), ' ');
        // compute and write the grade
        try
        {
            double final_grade = grade(students[i]);
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec);
        }
        catch (domain_error e)
        {
            cout << e.what();
        }
        cout << endl;
    }
}

int main()
{
    // demo_function1();
    // demo_const();
    // demo_functions();
    demo_student();
    return 0;
}