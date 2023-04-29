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

class Obj
{
public:
  std::string field1;
  size_t field2;
};

size_t hasher(const Obj &o)
{
  std::hash<std::string> hs;
  return hs(o.field1) + o.field2;
}

bool eq_op(const Obj &lhs, const Obj &rhs)
{
  return lhs.field1 == rhs.field1 && lhs.field2 == rhs.field2;
}

void demo_unordered()
{

  std::unordered_map<std::string, size_t> word_count;
  std::string word;

  std::stringstream ss("hello chatgpt say some words hello");
  while (ss >> word)
  {
    ++word_count[word];
  }

  describe_maplike(word_count.cbegin(), word_count.cend());

  // bucket
  LOG(word_count.bucket_count());
  LOG(word_count.max_bucket_count());
  LOG(word_count.bucket_size(0));
  LOG(word_count.bucket("hello"));
  LOG(word_count.bucket_size(word_count.bucket("hello")));

  LOG(word_count.load_factor());
  LOG(word_count.max_load_factor());

  word_count.rehash(10000); // 重组哈希表，let bucket_count > size/max_load_factor
  LOG(word_count.bucket_count());
  LOG(word_count.max_bucket_count());
  LOG(word_count.bucket_size(0));
  LOG(word_count.bucket("hello"));
  LOG(word_count.bucket_size(word_count.bucket("hello")));

  word_count.reserve(20000); // 重组哈希表，并且保证存n个元素的时候不会rehash，等于是预分配内存
  LOG(word_count.bucket_count());
  LOG(word_count.max_bucket_count());
  LOG(word_count.bucket_size(0));
  LOG(word_count.bucket("hello"));
  LOG(word_count.bucket_size(word_count.bucket("hello")));

  /*
  The difference is in purpose, although both are doing something similar.
  rehash takes an existing map and rebuilds a new size of buckets, rehashing in the process and redistributing elements into the new buckets.
  reserve guarantees you that if you don't insert more than the reserved number of elements, there will be no rehashing (i.e. your iterators will remain valid).
  */

  using obj_set = std::unordered_multiset<Obj, decltype(hasher) *, decltype(eq_op) *>;
  obj_set st(123, hasher, eq_op);
  st.insert({{"aaa", 1}, {"bbb", 2}});
  std::for_each(st.begin(), st.end(), [](const obj_set::key_type &obj) -> void
                { LOG(obj.field1);
                LOG(obj.field2); });
}

int main(int argc, char **argv)
{
  RUN_DEMO(demo_map);
  RUN_DEMO(demo_set);
  RUN_DEMO(demo_multi);
  RUN_DEMO(demo_pair);
  RUN_DEMO(demo_types);
  RUN_DEMO(demo_unordered);
  return EXIT_SUCCESS;
}
