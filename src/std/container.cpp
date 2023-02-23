#include <vector>
#include <iostream>
using namespace std;

template <typename T>
void describe_vector(const vector<T> v)
{
    cout << "[";

    auto iter = v.begin();
    if (iter != v.end())
    {
        cout << *iter;
        iter++;
    }

    for (; iter != v.end(); ++iter)
    {
        cout << ", " << *iter;
    }
    cout << "]" << endl;
};

void demo_vector()
{
    vector<int> vec;
    vec.reserve(10);
    describe_vector(vec);

    for (int i = 0; i < 10; ++i)
    {
        vec.push_back(i);
    }
    describe_vector(vec);

    vec[0] = 100;
    describe_vector(vec);
}

int main()
{
    demo_vector();
    return 0;
}