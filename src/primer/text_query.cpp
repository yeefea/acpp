#include <sstream>
#include "text_query.h"
#include "query_result.h"

TextQuery::TextQuery(std::istream &is) : file(new std::vector<std::string>)
{
  std::string text;
  while (getline(is, text))
  {
    int n = file->size();
    file->push_back(text); // add to file vector
    std::istringstream line(text);
    std::string word;
    while (line >> word)
    {
      auto &lines = wm[word];
      if (!lines)
      {
        // 把一个对象交给现成的shared_ptr管理，用shared_ptr::reset
        lines.reset(new std::set<TextQuery::line_no>);
      }
      lines->insert(n);
    }
  }
}

QueryResult TextQuery::query(const std::string &sought) const
{
  static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);

  auto loc = wm.find(sought);
  if (loc == wm.end())
  {
    return QueryResult(sought, nodata, file); // word not found
  }
  else
  {
    return QueryResult(sought, loc->second, file);
  }
}