#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <cctype>
#include "util.h"
#include "Student_info.h"

using std::cin;
using std::copy;
using std::cout;
using std::endl;
using std::string;
using std::vector;

using std::back_inserter;
using std::find;
using std::find_if;
using std::isalnum;
using std::search;

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

    typedef string::const_iterator StrIter; // typedef定义类型别名 类似于Go的type oriType newType

    StrIter i = str.begin();
    StrIter j;
    while (i != str.end())
    {
        // find_if接受3个参数，begin_iter, end_iter, predicate

        i = find_if(i, str.end(), not_space); // 找第一个非空格字符，返回迭代器
        j = find_if(i, str.end(), space);     // 找第一个空格，返回迭代器
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

bool is_palindrome(const string &s)
{

    // equal接受3个参数，begin_iter, end_iter, iter2

    // equal经典用法, 判断palindrome, begin, end, rbegin
    return equal(s.begin(), s.end(), s.rbegin());
}

void demo_equal()
{
    string s0 = "123123";
    string s1 = "123321";
    string s2 = "12321";

    cout << s0 << " is palindrome? " << is_palindrome(s0) << endl;
    cout << s1 << " is palindrome? " << is_palindrome(s1) << endl;
    cout << s2 << " is palindrome? " << is_palindrome(s2) << endl;
}

// not_url_char 判断单个字符c是否是URL字符
bool not_url_char(char c)
{
    static const string url_ch = "~;/?:@=&$-_.+!*'(),"; // 可以出现在url中的字符
    // find，查找url_ch中出现c的第一个位置
    // 字符集iter_begin, 字符集iter_end，要判断的字符
    // isalnum函数来自cctype
    return !(isalnum(c) || find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}

string::const_iterator url_end(string::const_iterator b, string::const_iterator e)
{

    return find_if(b, e, not_url_char);
}
string::const_iterator url_beg(string::const_iterator b, string::const_iterator e)
{

    static const string sep = "://";

    typedef string::const_iterator iter;
    iter i = b;

    // 找[i,e)之间 "://"的位置
    while ((i = search(i, e, sep.begin(), sep.end())) != e)
    {
        iter beg = i;
        while (beg != b && isalpha(beg[-1]))
        {
            // 往回找
            --beg;
        }
        if (beg != i && !not_url_char(i[sep.size()]))
        {
            // 找到了url
            return beg;
        }
        i += sep.size();
    }
    // 没找到返回pass-tail
    return e;
}

vector<string> find_urls(const string &s)
{

    vector<string> ret;

    typedef string::const_iterator iter;
    iter b = s.begin(), e = s.end();

    while (b != e)
    {

        b = url_beg(b, e);
        if (b != e)
        {
            iter after = url_end(b, e);
            ret.push_back(string(b, after));
            b = after;
        }
    }

    return ret;
}

void demo_find_search()
{

    string url_str = "123123123http://abc.com ccccc://xxx.dev";

    auto urls = find_urls(url_str);

    for (auto iter = urls.begin(); iter != urls.end(); ++iter)
    {

        cout << "url " << *iter << endl;
    }
}

bool did_all_hw(const Student_info &s)
{
    return ((find(s.homework.begin(), s.homework.end(), 0) == s.homework.end()));
}

int main()
{
    demo_copy();
    demo_find_if();
    demo_equal();
    demo_find_search();
    return 0;
}