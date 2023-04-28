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

  auto beg = word_count.begin();
  describe_maplike(word_count.begin(), word_count.end());

  // init list of pairs
  std::map<std::string, std::string> names = {
      {"aaa", "bbb"}, {"ccc", "ddd"}, {"eee", "fff"}};

  describe_maplike(names.begin(), names.end());
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
