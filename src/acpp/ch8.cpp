#include <iostream>

using std::cout;
using std::endl;

template <class T>
T max(const T &left, const T &right)
{
    return left > right ? left : right;
}

void demo1()
{

    double a = 0.0;
    double b = 1.0;
    double c = max(a, b);
    
    cout << a << " " << b << " " << c << endl;
}

int main()
{
    demo1();
    return 0;
}