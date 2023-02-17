#include <string>
#include <iostream>
#include "Student_info.h"

using namespace std;
int main()
{
    Student_info s(cin);

    cout << s.describe() << endl;

    return 0;
}