#include <bitset>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <random>
#include <regex>
#include <sstream>
#include <tuple>
#include <vector>

#include "utils.h"

void demo_tuple() {
  std::tuple<std::size_t, std::size_t, std::size_t> p1;

  auto x = std::get<0>(p1);
  auto y = std::get<1>(p1);
  auto z = std::get<2>(p1);

  std::cout << OUTPUT_VAL(x) << ", " << OUTPUT_VAL(y) << ", " << OUTPUT_VAL(z)
            << std::endl;

  decltype(p1) p2 = std::make_tuple(1, 2, 3);

  x = std::get<0>(p2);
  y = std::get<1>(p2);
  z = std::get<2>(p2);

  std::cout << OUTPUT_VAL(x) << ", " << OUTPUT_VAL(y) << ", " << OUTPUT_VAL(z)
            << std::endl;

  std::get<2>(p2) = 555;  // write

  x = std::get<0>(p2);
  y = std::get<1>(p2);
  z = std::get<2>(p2);
  std::cout << OUTPUT_VAL(x) << ", " << OUTPUT_VAL(y) << ", " << OUTPUT_VAL(z)
            << std::endl;

  auto sz = std::tuple_size<decltype(p1)>::value;
  std::cout << OUTPUT_VAL(sz) << std::endl;

  // 第一个元素的类型std::tuple_element<1, decltype(p1)>::type
  std::tuple_element<1, decltype(p1)>::type yy = std::get<1>(p1);

  std::cout << OUTPUT_VAL(yy) << std::endl;

  std::tuple<std::size_t, std::size_t> p3;

  bool less = p1 < p2;
  std::cout << std::boolalpha;
  std::cout << OUTPUT_VAL(less) << std::noboolalpha << std::endl;

  // less = p1 < p3;  这样不能编译，成员数量不同，不能比较
}

void demo_bitset() {
  std::bitset<32> bitvec(1U);

  std::cout << OUTPUT_VAL(bitvec) << std::endl;

  std::bitset<13> bitvec1(0xbeef);  // 高位被丢弃
  std::bitset<20> bitvec2(0xbeef);
  std::bitset<80> bitvec3(~0ULL);  // 高位补0

  std::bitset<32> bitvec4("1100");

  std::string bits("11111111000000000011001101");
  std::bitset<32> bitvec5(bits, 5, 4);
  std::bitset<32> bitvec6(bits, bits.size() - 4);

  std::cout << OUTPUT_VAL(bitvec1) << std::endl;
  std::cout << OUTPUT_VAL(bitvec2) << std::endl;
  std::cout << OUTPUT_VAL(bitvec3) << std::endl;
  std::cout << OUTPUT_VAL(bitvec4) << std::endl;
  std::cout << OUTPUT_VAL(bitvec5) << std::endl;
  std::cout << OUTPUT_VAL(bitvec6) << std::endl;
  bitvec6.flip();
  std::cout << OUTPUT_VAL(bitvec6) << std::endl;
  std::cout << OUTPUT_VAL(bitvec6.to_string('a', 'b')) << std::endl;
}

void demo_regex() {
  // regex
  // regex_match(test_str, regex, flag)
  // regex_search(test_str, match_result, regex, flag)
  // regex_replace
  // regex_iterator

  // smatch
  // ssub_match

  std::string pattern("[^c]ei");
  pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
  std::regex r(pattern, std::regex::icase);

  std::cout << "sub expression count: " << OUTPUT_VAL(r.mark_count())
            << std::endl;

  std::cout << "flags: " << OUTPUT_VAL(r.flags()) << std::endl;

  std::smatch results;  // 保存搜索结果

  std::string test_str = "receipt freind theif receive";
  if (std::regex_search(test_str, results, r)) {  // search
    std::cout << results.str() << std::endl;
  }

  std::cout << "sregex_iter>>" << std::endl;

  // regex迭代器
  // std::sregex_iterator会反复调用regex_search
  for (std::sregex_iterator it(test_str.begin(), test_str.end(), r), end_it;
       it != end_it; ++it) {
    auto pos = it->prefix().length();
    pos = pos > 5 ? pos - 5 : 0;

    std::cout << it->prefix().str().substr(pos) << "\t>>>" << it->str()
              << "<<<\t" << it->suffix().str().substr(0, 5) << std::endl;
  }

  try {
    r = std::regex("[aaaaa", std::regex::icase);
  } catch (std::regex_error e) {
    std::cout << "parse regex failed, ";
    // code定义在std::regex_constants::error_type
    std::cout << e.what() << "\ncode: " << e.code() << std::endl;
  }

  // char* 用cmatch来接
  // std::string 用smatch来接
  // 还有wsmatch, wcmatch
  std::cmatch cresults;
  if (regex_search("receipt freind theif receive", cresults, r)) {
    std::cout << cresults.str() << std::endl;
  }

  // 子表达式 "()"

  std::regex rfiles("([[:alnum:]]+)\\.(cpp|cxx|cc)$", std::regex::icase);

  cresults = std::cmatch();
  std::cout << "sub regex>>>" << std::endl;
  if (std::regex_search("aaa.cxx aaa.cc jjj.java abc.cpp", cresults, rfiles)) {
    // .str(1)表示第一个子表达式
    std::cout << OUTPUT_VAL(cresults.str(0)) << std::endl;  // default 0
    std::cout << OUTPUT_VAL(cresults.str(1)) << std::endl;
    std::cout << OUTPUT_VAL(cresults.str(2)) << std::endl;
    std::cout << OUTPUT_VAL(cresults.str(3)) << std::endl;  // empty
  }

  std::string filenames("aaa.cxx aaa.cc jjj.java abc.cpp");
  for (std::sregex_iterator it(filenames.begin(), filenames.end(), rfiles),
       end_it;
       it != end_it; ++it) {
    std::cout << it->str() << std::endl;
  }
}

bool valid(const std::smatch& m) {
  if (m[1].matched) {
    return m[3].matched && (m[4].matched == 0 || m[4].str() == " ");
  } else {
    return !m[3].matched && m[4].str() == m[6].str();
  }
}

void demo_regex_sub_match() {
  // 子匹配
  std::string rphone_str =
      "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
  //     1     2       3      4       5        6       7
  std::regex r(rphone_str);
  std::smatch m;

  std::string s1 = "(123)-456-7890";
  std::string s2 = "(123) 456-7890";

  std::vector<std::string> files = {s1, s2};

  for (const auto& s : files) {
    for (std::sregex_iterator it(s.begin(), s.end(), r), end_it; it != end_it;
         ++it) {
      if (valid(*it)) {
        std::cout << "valid: ";
      } else {
        std::cout << "not valid: ";
      }
      std::cout << it->str() << std::endl;
    }
  }
}
void demo_regex_replace() {
  // 子匹配
  std::string rphone_str =
      "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
  //     1     2       3      4       5        6       7
  std::regex r(rphone_str);
  // std::smatch m;
  std::string s("yeefea: (123) 456-7890");
  std::string fmt = "$2.$5.$7";
  std::cout << std::regex_replace(s, r, fmt)
            << std::endl;  // 只会替换匹配的部分，默认其余部分原样输出

  std::cout << std::regex_replace(s, r, fmt,
                                  std::regex_constants::format_no_copy)
            << std::endl;  // 改变行为，不输出其余部分
}
void demo_random() {
  // 局部随机引擎和分布应该定义为static，否则每次执行demo函数都生成相同的随机序列
  static std::default_random_engine e;
  // 如果想要每次运行程序得到不同的序列，则需要设置seed
  // static std::default_random_engine e(time(0));
  // 这里time不是一个好的seed，只是作为一个例子

  for (std::size_t i = 0; i < 10; ++i) {
    std::cout << e()
              << " ";  // 随机引擎返回的随机数一般不直接用，这里只是个例子
  }
  std::cout << std::endl;

  static std::uniform_int_distribution<unsigned> u(0, 9);  // 均匀分布

  static std::normal_distribution<> n(4, 1.5);  // 正态分布

  std::vector<unsigned> vals(9);

  for (size_t i = 0; i != 200; ++i) {
    unsigned v = std::lround(n(e));  // 将随机引擎直接传给随机分布
    if (v < vals.size()) {
      ++vals[v];
    }
  }
  for (size_t j = 0; j != vals.size(); ++j) {
    std::cout << j << ": " << std::string(vals[j], '*') << std::endl;
  }
}

void demo_io() {
  // iomanip
  // bool
  std::cout << "default bool: " << true << " " << false << std::endl;
  std::cout << "alpha bool: " << std::boolalpha << true << " " << false;
  std::cout << std::noboolalpha << std::endl;
  // int
  std::cout << std::showbase;
  std::cout << "default: " << 1024 << std::endl;
  std::cout << "octal: " << std::oct << 1024 << std::endl;
  std::cout << "hex: " << std::hex << 15 << " " << 1024 << std::endl;
  std::cout << std::uppercase;
  std::cout << "hex: " << std::hex << 15 << " " << 1024 << std::endl;
  std::cout << std::nouppercase;
  std::cout << "decimal: " << std::dec << 1024 << std::endl;
  std::cout << std::noshowbase;

  std::stringstream ss("123abc");

  // 未格式化IO
  // is.get(ch)
  // os.put(ch)
  // is.get() -> int
  // is.putback(ch)
  // is.unget()
  // is.peek()

  char ch;
  while (ss.get(ch)) {
    std::cout.put(ch);
  }
  std::cout << std::endl;
  std::cout << OUTPUT_VAL(ss.tellg()) << std::endl;

  int ich;  // 注意get的返回值是int，EOF定义为-1
  // 如果写成 unsigned char，会死循环
  while ((ich = ss.get()) != EOF) {
    std::cout.put(char(ich));
  }
  std::cout << "EOF" << std::endl;

  ss = std::stringstream("123abcdefghijk");
  for (int i = 0; i < 5; ++i) {
    ss.get(ch);
    std::cout.put(ch);
  }

  // seekg get, istream
  // seekp put, ostream

  // tellg get, istream
  // tellp put, ostream
  // 经测试发现，如果已经读到了-1，就无法再seek回0了
  ss.seekg(0);
  while ((ich = ss.get()) != EOF) {
    std::cout.put(char(ich));
  }
}
int main(int argc, char** argv) {
  RUN_DEMO(demo_tuple);
  RUN_DEMO(demo_bitset);
  RUN_DEMO(demo_regex);
  RUN_DEMO(demo_regex_sub_match);
  RUN_DEMO(demo_regex_replace);
  RUN_DEMO(demo_random);
  RUN_DEMO(demo_random);
  RUN_DEMO(demo_io);
  return EXIT_SUCCESS;
}