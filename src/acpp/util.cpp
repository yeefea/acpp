#include <iostream>
#include <string>
#include <vector>
#include "util.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

void describe_int_vector(const vector<int> &strs)
{

    cout << "[ ";
    for (auto iter = strs.begin(); iter != strs.end();)
    {
        cout << *iter;
        ++iter;
        if (iter != strs.end())
        {
            cout << ",";
        }
        cout << " ";
    }
    cout << "] size: " << strs.size() << endl;
}

void describe_string_vector(const vector<string> &strs)
{
    cout << "[ ";
    for (auto iter = strs.begin(); iter != strs.end();)
    {
        cout << "\"" << *iter << "\"";
        ++iter;
        if (iter != strs.end())
        {
            cout << ",";
        }
        cout << " ";
    }
    cout << "] size: " << strs.size() << endl;
}