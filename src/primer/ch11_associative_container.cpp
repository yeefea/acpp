#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "utils.h"

void demo_map() {
  std::map<std::string, size_t> word_count;

  std::stringstream ss("aaaaa bbb asdf asdf asdf ccc");

  std::string word;
  while (ss >> word) {
    ++word_count[word];
  }

  auto beg = word_count.begin();
  describe_maplike(word_count.begin(), word_count.end());
  
}

void demo_set() {}
int main(int argc, char **argv) {
  RUN_DEMO(demo_map);
  RUN_DEMO(demo_set);
  return EXIT_SUCCESS;
}
