#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <numeric>
#include <cctype>
#include <stdexcept>
#include <iterator>
#include <iomanip>
#include "util.h"
#include "Student_info.h"
#include "grade.h"
#include "median.h"

using std::accumulate;     // <numeric>
using std::back_inserter;  // <iterator>
using std::cin;            // <iostream>
using std::copy;           // <algorithm>
using std::cout;           // <iostream>
using std::domain_error;   // <stdexcept>
using std::endl;           // <iostream>
using std::find;           // <algorithm>
using std::find_if;        // <algorithm>
using std::isalnum;        // <cctype>
using std::ostream;        // <iostream>
using std::remove_copy;    // <algorithm>
using std::remove_copy_if; // <algorithm>
using std::search;         // <algorithm>
using std::setprecision;   // <iomanip>
using std::string;         // <string>
using std::transform;      // <algorithm>
using std::vector;         // <vector>

template <typename T>
void describe_vector(const std::vector<T> &items)
{
    cout << "[ ";
    for (auto iter = items.begin(); iter != items.end();)
    {
        cout << "\"" << *iter << "\"";
        ++iter;
        if (iter != items.end())
        {
            cout << ",";
        }
        cout << " ";
    }
    cout << "] size: " << items.size() << endl;
}

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

    copy+back_inserter类似于Go语言的append
    */
    copy(vec2.begin(), vec2.end(), back_inserter(vec1)); // vec1 = append(vec1, vec2...)
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
double grade_aux(const Student_info &s)
{
    try
    {
        return grade(s);
    }
    catch (domain_error)
    {
        return grade(s.midterm, s.final, 0);
    }
}

double median_analysis(const vector<Student_info> &students)
{
    vector<double> grades;

    // 因为grade函数有重载，所以无法作为transform的参数
    transform(students.begin(), students.end(), back_inserter(grades), grade_aux);
    return median(grades);
}

void write_analysis(ostream &out,
                    const string &name,
                    double analysis(const vector<Student_info> &),
                    const vector<Student_info> &did,
                    const vector<Student_info> &didnt)
{
    out << name << ": median(did) = " << analysis(did) << ", median(didnt) = " << analysis(didnt) << endl;
}

double average(const vector<double> &v)
{
    // 注意这里一定不能写0，要写0.0
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}
double average_grade(const Student_info &s)
{
    return grade(s.midterm, s.final, average(s.homework));
}

double average_analysis(const vector<Student_info> &students)
{
    vector<double> grades;
    transform(students.begin(), students.end(), back_inserter(grades), average_grade);
    return median(grades);
}
double optimistic_median(const Student_info &s)
{
    vector<double> nonzero;
    // remove_copy 类似于filter
    remove_copy(s.homework.begin(), s.homework.end(), back_inserter(nonzero), 0);
    if (nonzero.empty())
    {
        return grade(s.midterm, s.final, 0.0);
    }
    return grade(s.midterm, s.final, median(nonzero));
}

double optimistic_median_analysis(const vector<Student_info> &s)
{
    vector<double> grades;
    transform(s.begin(), s.end(), back_inserter(grades), optimistic_median);
    return median(grades);
}

void demo_function_parameter()
{

    // students who did and didn't do all their homework
    vector<Student_info> did, didnt;
    // read the student records and partition them
    Student_info student;
    while (read(cin, student))
    {
        if (did_all_hw(student))
            did.push_back(student);
        else
            didnt.push_back(student);
    }
    // verify that the analyses will show us something
    if (did.empty())
    {
        cout << "No student did all the homework!" << endl;
        return;
    }
    if (didnt.empty())
    {
        cout << "Every student did all the homework!" << endl;
        return;
    }
    // do the analyses
    auto prec = cout.precision();
    setprecision(3);
    write_analysis(cout, "median", median_analysis, did, didnt);
    write_analysis(cout, "average", average_analysis, did, didnt);
    write_analysis(cout, "median of homework turned in",
                   optimistic_median_analysis, did, didnt);
    setprecision(prec);
}

bool pgrade(const Student_info &s)
{
    return !fgrade(s);
}
vector<Student_info> extract_fails(
    vector<Student_info> &students)
{
    vector<Student_info> fail;
    remove_copy_if(students.begin(), students.end(), back_inserter(fail), pgrade);
    students.erase(
        remove_if(students.begin(), students.end(), fgrade),
        students.end());
    return fail;
}

bool is_zero(int x)
{
    return x == 0;
}

bool is_even(int x)
{
    return x % 2 == 0;
}

void demo_remove_copy_if()
{
    // 原地删除，把满足remove条件的一到末尾，不满足的移到前面。并不会缩小vector size，需要调用erase
    // remove
    cout << ">>> remove" << endl;
    vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto new_end = remove(v.begin(), v.end(), 3);
    describe_vector(v);
    v.erase(new_end, v.end()); // shrink
    describe_vector(v);

    // remove_if
    cout << ">>> remove_if" << endl;
    new_end = remove_if(v.begin(), v.end(), is_zero);
    describe_int_vector(v);
    v.erase(new_end, v.end()); // shrink
    describe_int_vector(v);

    vector<int> new_v;
    // copy
    cout << ">>> copy" << endl;
    copy(v.begin(), v.end(), back_inserter(new_v));
    describe_int_vector(new_v);

    // copy_if
    new_v.clear();
    cout << ">>> copy_if" << endl;
    copy_if(v.begin(), v.end(), back_inserter(new_v), is_even);
    describe_int_vector(new_v);

    // 原来的vector不动
    // 效果是新的vector里去除了给定的元素，类似于filter out的效果
    // 例子：
    // [0,1,2,3,4,5,6,7,8,9] remove_copy_if is_even
    // 得到新的vector[1,3,5,7,9]，is_even的数字不会被拷贝出来
    // remove copy
    cout << ">>> remove_copy" << endl;
    new_v.clear();
    // filter out 2
    remove_copy(v.begin(), v.end(), back_inserter(new_v), 2); // filter out 2
    describe_int_vector(new_v);

    cout << ">>> remove_copy_if" << endl;
    new_v.clear();
    // filter out even numbers
    remove_copy_if(v.begin(), v.end(), back_inserter(new_v), is_even);
    describe_int_vector(new_v);
}

vector<Student_info>
extract_fails_partition(vector<Student_info> &students)
{
    vector<Student_info>::iterator iter =
        stable_partition(students.begin(), students.end(), pgrade);
    vector<Student_info> fail(iter, students.end());
    students.erase(iter, students.end());

    return fail;
}
string getname(const Student_info &s)
{
    return s.name;
}
void demo_partition()
{
    vector<Student_info> students;
    students.push_back(Student_info{"test1", 99, 98});
    students.push_back(Student_info{"test2", 59, 58});

    auto fails = extract_fails_partition(students);
    vector<string> students_pass, students_fail;
    transform(students.begin(), students.end(), back_inserter(students_pass), getname);
    transform(fails.begin(), fails.end(), back_inserter(students_fail), getname);

    cout << "students pass: ";
    describe_string_vector(students_pass);
    cout << "students fail: ";
    describe_string_vector(students_fail);
    // describe_string_vector

    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int true_arr[5] = {0};
    int false_arr[5] = {0};

    std::partition_copy(std::begin(arr), std::end(arr),
                        std::begin(true_arr), std::begin(false_arr),
                        [](int i)
                        { return 4 < i; });

    cout << "true_arr:  " << true_arr << endl;
    cout << "false_arr: " << false_arr << endl;
}

int main()
{
    demo_copy();
    demo_find_if();
    demo_equal();
    demo_find_search();
    // demo_function_parameter();
    demo_remove_copy_if();
    demo_partition();
    return 0;
}