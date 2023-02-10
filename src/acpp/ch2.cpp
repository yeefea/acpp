#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

void demo_while_loop()
{
    cout << "enter your first name: ";
    string name;
    cin >> name;
    const string greeting = "hello, " + name + "!";

    const int pad = 1;
    const int rows = pad * 2 + 3;
    const string::size_type cols = greeting.size() + pad * 2 + 2;

    cout << endl;

    for (int r = 0; r != rows; ++r)
    {
        string::size_type c = 0;

        while (c != cols)
        {
            // is it time to write the greeting?
            if (r == pad + 1 && c == pad + 1)
            {
                cout << greeting;
                c += greeting.size();
            }
            else
            {
                // are we on the border?
                if (r == 0 || r == rows - 1 ||
                    c == 0 || c == cols - 1)
                    cout << "*";
                else
                    cout << " ";
                ++c;
            }
        }
        cout << endl;
    }
}

void demo_for_loop()
{
    const int rows = 10;
    for (int r = 1; r <= rows; ++r)
    {
        cout << r << " ";
    }

    cout << endl;
}

void demo_types()
{

    bool b = true;

    unsigned u = 10;
    short s = 11;
    long l = 12;
    size_t z = 100;
    string::size_type sz = 101;
    cout << "bool " << b << endl;
    cout << "unsigned " << u << endl;
    cout << "short " << s << endl;
    cout << "long " << l << endl;
    cout << "size_t " << z << endl;
    cout << "string::size_type " << sz << endl;

    // strings
    string s0;
    string s1 = "a";
    string s2(100, 'c');
}
int main()
{
    // demo_while_loop();
    // demo_for_loop();
    demo_types();
    return 0;
}
