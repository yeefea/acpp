#include <map>
#include <unordered_map>
#include <string>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

using std::map;
using std::string;
using std::unordered_map;

void demo_map()
{

    map<string, int> counters;

    string s;

    while (cin >> s)
    {
        ++counters[s];
    }

    for (auto it = counters.begin(); it != counters.end(); ++it)
    {
        cout << it->first << "\toccurred " << it->second << "times" << endl;
    }
}

int main()
{

    demo_map();
    return 0;
}