#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::setprecision;
using std::streamsize;
using std::string;
using std::vector;

void demo_grades()
{
    // ask for and read the student's name
    cout << "Please enter your first name: ";
    string name;
    cin >> name;
    cout << "Hello, " << name << "!" << endl;
    // ask for and read the midterm and final grades
    cout << "Please enter your midterm and final exam grades: ";
    double midterm, final;
    cin >> midterm >> final;
    // ask for the homework grades
    cout << "Enter all your homework grades, "
            "followed by end-of-file: ";
    // the number and sum of grades read so far
    int count = 0;
    double sum = 0;
    // a variable into which to read
    double x;

    // invariant:
    // we have read count grades so far, and
    // sum is the sum of the first count grades
    while (cin >> x)
    {
        ++count;
        sum += x;
    }
    // write the result
    streamsize prec = cout.precision();

    cout << "Your final grade is " << setprecision(3)
         << 0.2 * midterm + 0.4 * final + 0.4 * sum / count
         << setprecision(prec) << endl;
}

void demo_grades2()
{
    // ask for and read the student's name
    cout << "Please enter your first name: ";
    string name;
    cin >> name;
    cout << "Hello, " << name << "!" << endl;
    // ask for and read the midterm and final grades
    cout << "Please enter your midterm and final exam grades: ";
    double midterm, final;
    cin >> midterm >> final;
    // ask for the homework grades
    cout << "Enter all your homework grades, "
            "followed by end-of-file: ";
    // the number and sum of grades read so far
    // int count = 0;
    double sum = 0;
    // a variable into which to read
    double x;

    vector<double> homework;

    // invariant:
    // we have read count grades so far, and
    // sum is the sum of the first count grades
    while (cin >> x)
    {
        homework.push_back(x);
    }
    sort(homework.begin(), homework.end());

    auto size = homework.size();
    auto mid = size / 2;
    double median;

    if (size == 0)
    {
        median = 0.0;
    }
    else
    {
        median = size % 2 == 0 ? (homework[mid] + homework[mid - 1]) / 2 : homework[mid];
    }

    cout << "Your median is " << median << endl;
    // write the result
    streamsize prec = cout.precision();
    // auto prec = cout.precision();

    // 迭代vector
    for (auto it = homework.begin(); it != homework.end(); it++)
    {
        sum += *it;
    }

    double avg = homework.size() == 0 ? 0.0 : sum / homework.size();

    cout << "Your final grade is " << setprecision(3)
         << 0.2 * midterm + 0.4 * final + 0.4 * avg
         << setprecision(prec) << endl;
}

int main()
{
    // demo_grades();
    demo_grades2();
    return 0;
}