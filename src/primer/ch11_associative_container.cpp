#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <iterator>
#include <CoreWLAN/CoreWLAN.h>
#include "utils.h"

void demo_map()
{
  std::map<std::string, size_t> word_count;

  std::stringstream ss("aaaaa bbb asdf asdf asdf ccc");

  std::string word;
  while (ss >> word)
  {
    ++word_count[word];
  }

  std::map<std::string, size_t>::iterator beg = word_count.begin();
  describe_maplike(word_count.begin(), word_count.end());

  // init list of pairs
  std::map<std::string, std::string> names = {
      {"aaa", "bbb"}, {"ccc", "ddd"}, {"eee", "fff"}};

  describe_maplike(names.begin(), names.end());

  // CRUD
  // C/U
  auto ret = word_count.insert({"123", 1});
  std::cout << "inserted: " << ret.second << std::endl;
  word_count.insert(std::make_pair("123", 1));
  word_count.insert(std::pair<std::string, int>("123", 1));
  word_count.insert(std::map<std::string, int>::value_type("123", 1));
  auto it = word_count.insert(word_count.begin(), {"123", 1});
  it = word_count.insert(it, {"124", 1});

  // R
  LOG(word_count["123"]);
  if (word_count.find("125") == word_count.end())
  {
    std::cout << "word not found" << std::endl;
  }
  else
  {
    std::cout << "word found" << std::endl;
  }

  // D
  if (word_count.erase("123"))
  {
    std::cout << "word removed" << std::endl;
  }
  else
  {
    std::cout << "word not found" << std::endl;
  }
}

bool predicate_shorter(const std::string &a, const std::string &b)
{
  return a.size() < b.size();
}

void demo_set()
{
  std::set<std::string> exclude = {"aaaaa", "bbb"};
  std::stringstream ss("aaaaa bbb asdf asdf asdf ccc");

  std::map<std::string, size_t> word_count;
  std::string word;
  while (ss >> word)
  {
    // 跳过出现在exclude里的单词
    if (exclude.find(word) == exclude.end())
    {
      ++word_count[word];
    }
  }

  auto beg = word_count.begin();
  describe_maplike(word_count.begin(), word_count.end());

  std::set<std::string> words = {"ccc", "bbbb", "a", "ee"};

  // predicate
  std::set<std::string, decltype(predicate_shorter) *> ordered_words(
      predicate_shorter);
  std::copy(words.cbegin(), words.cend(), std::inserter(ordered_words, ordered_words.end()));
  describe_sequential_container(ordered_words.cbegin(), ordered_words.cend());
}

void demo_multi()
{
  std::vector<int> ivec;
  for (decltype(ivec)::size_type i = 0; i != 10; ++i)
  {
    ivec.push_back(i);
    ivec.push_back(i);
  }

  std::set<decltype(ivec)::value_type> iset(ivec.cbegin(), ivec.cend());
  std::multiset<decltype(ivec)::value_type> miset(ivec.cbegin(), ivec.cend());
  std::unordered_multiset<decltype(ivec)::value_type> umiset(ivec.cbegin(),
                                                             ivec.cend());
  describe_sequential_container(iset.cbegin(), iset.cend());
  describe_sequential_container(miset.cbegin(), miset.cend());
  describe_sequential_container(umiset.cbegin(), umiset.cend());

  auto x = umiset.find(1);

  std::multiset<std::string> c;

  std::vector<std::string> svec;

  std::copy(svec.begin(), svec.end(), std::inserter(c, c.end()));
  // error set不能用back_inserter，因为没有push_back函数
  // std::copy(svec.begin(), svec.end(), std::back_inserter(c));
  std::copy(c.begin(), c.end(), std::inserter(svec, svec.end()));
  std::copy(c.begin(), c.end(), std::back_inserter(svec));
}

std::pair<std::string, int> some_function_return_pair()
{
  return {"abc", 123};
}

void demo_pair()
{
  std::pair<std::string, std::string> anon;
  std::pair<std::string, size_t> word_count;
  std::pair<std::string, std::vector<int>> line =
      std::make_pair<std::string, std::vector<int>>("123123",
                                                    {1, 2, 3, 1, 2, 3});
  auto pr = some_function_return_pair();
  LOG(pr.first);
  LOG(pr.second);
}

void demo_types()
{
  std::set<std::string>::key_type kv;   // string
  std::set<std::string>::value_type sv; // string

  std::map<std::string, int>::key_type mk;    // string
  std::map<std::string, int>::mapped_type mm; // int
  std::map<std::string, int>::value_type mv;  // pair
}

int main(int argc, char **argv)
{
  RUN_DEMO(demo_map);
  RUN_DEMO(demo_set);
  RUN_DEMO(demo_multi);
  RUN_DEMO(demo_pair);
  RUN_DEMO(demo_types);
  return EXIT_SUCCESS;
}
