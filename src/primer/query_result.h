#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <set>
#include <map>
#include <vector>
#include "text_query.h"

// using line_no = TextQuery::line_no;

class QueryResult
{
  friend std::ostream &print_query_result(std::ostream &, const QueryResult &);

public:
  QueryResult(std::string s,
              std::shared_ptr<std::set<TextQuery::line_no>> p,
              std::shared_ptr<std::vector<std::string>> f)
      : sought(s), lines(p), file(f) {}
  std::set<TextQuery::line_no>::iterator begin()
  {
    return lines->begin();
  }
  std::set<TextQuery::line_no>::iterator end()
  {
    return lines->end();
  }
  std::shared_ptr<std::vector<std::string>> get_file()
  {
    return file;
  }

private:
  std::string sought;
  std::shared_ptr<std::set<TextQuery::line_no>> lines;
  std::shared_ptr<std::vector<std::string>> file;
};