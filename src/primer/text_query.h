#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <set>

class QueryResult;

class TextQuery
{
public:
  using line_no = std::vector<std::string>::size_type;
  TextQuery(std::istream &);
  QueryResult query(const std::string &) const;

private:
  std::shared_ptr<std::vector<std::string>> file;
  std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};