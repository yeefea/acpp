#include <string>
#include <iostream>
#include "Student_info.h"

using namespace std;
int main()
{
    Student_info s;
    s.read(std::cin);

    cout << s.get_name() << endl;

    return 0;
}