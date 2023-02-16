#include <map>
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib>

using std::cin;
using std::cout;
using std::domain_error;
using std::endl;
using std::getline; // <iostream>
using std::istream;
using std::logic_error;
using std::map;
using std::rand; // <cstdlib>
using std::string;
using std::unordered_map;
using std::vector;
// return a random integer in the range [0, n)
int nrand(int n)
{
    if (n <= 0 || n > RAND_MAX)
        throw domain_error("Argument to nrand is out of range");
    const int bucket_size = RAND_MAX / n;
    int r;
    do
        r = rand() / bucket_size;
    while (r >= n);
    return r;
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

// xref 函数签名含有默认参数
map<string, vector<int>> xref(istream &in, vector<string> find_words(const string &) = split)
{
    string line;
    int line_number = 0;
    map<string, vector<int>> ret;

    // read
    while (getline(in, line))
    {
        ++line_number;

        vector<string> words = find_words(line);

        for (vector<string>::const_iterator it = words.begin();
             it != words.end();
             ++it)
        {
            // append to vector !!!
            ret[*it].push_back(line_number);
        }
    }
    return ret;
}

void demo_xref()
{

    // call xref using split by default
    map<string, vector<int>> ret = xref(cin);

    // output
    for (map<string, vector<int>>::const_iterator it = ret.begin();
         it != ret.end(); ++it)
    {
        // write the word
        cout << it->first << " occurs on line(s): ";
        // followed by one or more line numbers
        vector<int>::const_iterator line_it = it->second.begin();
        cout << *line_it; // write the first line number
        ++line_it;
        // write the rest of the line numbers, if any
        while (line_it != it->second.end())
        {
            cout << ", " << *line_it;
            ++line_it;
        }
        cout << endl;
    }
}

void demo_map()
{
    cout << "word count" << endl;

    map<string, int> counters;

    string s;

    while (cin >> s)
    {
        ++counters[s];
    }
    // 迭代
    for (map<string, int>::const_iterator it = counters.begin(); it != counters.end(); ++it)
    {
        // first: key
        // second: value
        cout << it->first << "\toccurred " << it->second << "times" << endl;
    }
}

typedef vector<string> Rule;
typedef vector<Rule> Rule_collection;
typedef map<string, Rule_collection> Grammar;

Grammar read_grammar(istream &in)
{
    Grammar ret;
    string line;
    // read the input
    while (getline(in, line))
    {
        // split the input into words
        vector<string> entry = split(line);
        if (!entry.empty())
            // use the category to store the associated rule
            ret[entry[0]].push_back(
                Rule(entry.begin() + 1, entry.end()));
    }
    return ret;
}
bool bracketed(const string &s)
{
    return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}
void gen_aux(const Grammar &g, const string &word, vector<string> &ret)
{
    if (!bracketed(word))
    {
        ret.push_back(word);
    }
    else
    {
        // locate the rule that corresponds to word
        Grammar::const_iterator it = g.find(word);
        if (it == g.end())
            throw logic_error("empty rule");
        // fetch the set of possible rules
        const Rule_collection &c = it->second;
        // from which we select one at random
        const Rule &r = c[nrand(c.size())];
        // recursively expand the selected rule
        for (Rule::const_iterator i = r.begin(); i != r.end(); ++i)
            gen_aux(g, *i, ret);
    }
}
vector<string> gen_sentence(const Grammar &g)
{
    vector<string> ret;
    gen_aux(g, "<sentence>", ret);
    return ret;
}
void demo_grammar()
{
    // generate the sentence
    vector<string> sentence = gen_sentence(read_grammar(cin));
    // write the first word, if any
    vector<string>::const_iterator it = sentence.begin();
    if (!sentence.empty())
    {
        cout << *it;
        ++it;
    }

    // write the rest of the words, each preceded by a space
    while (it != sentence.end())
    {
        cout << " " << *it;
        ++it;
    }
    cout << endl;
}
int main()
{
    demo_map();
    // demo_xref();
    // demo_grammar();
    return 0;
}