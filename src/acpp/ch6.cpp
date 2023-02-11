#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <cctype>
#include "util.h"

using std::back_inserter;
using std::cin;
using std::copy;
using std::cout;
using std::endl;
using std::find_if;
using std::string;
using std::vector;

void demo_copy()
{
    vector<int> vec0;
    describe_int_vector(vec0);

    vector<int> vec1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    describe_int_vector(vec1);
    vector<int> vec2 = {-1, -2, -3};
    describe_int_vector(vec2);

    // copy 范型算法
    // back_inserter iterator adaptor迭代适配器

    /*

    copy（begin, end, out)
    等价于
    while (begin != end){
        *out++ = *begin++
    }
    */
    copy(vec2.begin(), vec2.end(), back_inserter(vec1));
    describe_int_vector(vec1);

    // vec2.insert(vec2.end(), vec1.begin(), vec1.end());
    // describe_int_vector(vec2);
}

bool space(char c)
{
    return isspace(c);
}
bool not_space(char c)
{
    return !isspace(c);
}

vector<string> split(const string &str)
{

    vector<string> ret;

    string::const_iterator i = str.begin();
    string::const_iterator j;
    while (i != str.end())
    {
        i = find_if(i, str.end(), not_space); // 找第一个非空格字符
        j = find_if(i, str.end(), space);     // 找第一个空格
        if (i != str.end())
        {
            ret.push_back(string(i, j));
        }
        i = j;
    }
    return ret;
}

void demo_find_if()
{

    string s = "123123 456 7890";
    vector<string> sp = split(s);

    describe_string_vector(sp);
}

bool is_palindrome(const string& s){
    return equal(s.begin(), s.end(), s.rbegin());
}

void demo_equal(){

    string s0 = "123123";
    string s1 = "123321";
    string s2 = "12321";

    cout << s0 << " is palindrome? "<< is_palindrome(s0) << endl;
    cout << s1 << " is palindrome? "<< is_palindrome(s1) << endl;
    cout << s2 << " is palindrome? "<< is_palindrome(s2) << endl;

}

int main()
{
    demo_copy();
    demo_find_if();
    demo_equal();
    return 0;
}