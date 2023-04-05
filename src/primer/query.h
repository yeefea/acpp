#pragma once
#include <string>
#include <memory>
#include <iostream>
#include <set>
#include <iterator>
#include "text_query.h"
#include "query_result.h"

/*
QueryBase
- WordQuery
- NotQuery
- BinaryQuery
  - AndQuery
  - OrQuery

Query->QueryBase
*/

class Query;

class QueryBase
{
  friend class Query; // friend class

protected:
  using line_no = TextQuery::line_no;
  virtual ~QueryBase() = default;

private:
  virtual QueryResult eval(const TextQuery &) const = 0; // pure virtual
  virtual std::string rep() const = 0;                   // pure virtual
};

// Query 接口类，管理QueryBase的子类
class Query
{
  friend Query operator~(const Query &);
  friend Query operator|(const Query &, const Query &);
  friend Query operator&(const Query &, const Query &);

public:
  Query(const std::string &);
  QueryResult eval(const TextQuery &t) const // call overrided method eval()
  {
    return q->eval(t);
  }
  std::string rep() const
  {
    return q->rep();
  }

private:
  Query(std::shared_ptr<QueryBase> query) : q(query) {} // private构造函数，只有friend能访问
  std::shared_ptr<QueryBase> q;                         // 指针支持polymorphism
};

// 运算符<<
std::ostream &operator<<(std::ostream &os, const Query &query)
{
  return os << query.rep();
}

class WordQuery : public QueryBase
{
  friend class Query;
  std::string query_word;
  WordQuery(const std::string &s) : query_word(s) {}
  QueryResult eval(const TextQuery &t) const
  {
    return t.query(query_word);
  }
  std::string rep() const { return query_word; }
};

// Query构造函数
inline Query::Query(const std::string &s) : q(new WordQuery(s)) {}

class NotQuery : public QueryBase
{
  friend Query operator~(const Query &);
  Query query;

  NotQuery(const Query &q) : query(q) {}
  std::string rep() const { return "~(" + query.rep() + ")"; }
  QueryResult eval(const TextQuery &) const;
};

// 运算符~
inline Query operator~(const Query &operand)
{
  return std::shared_ptr<QueryBase>(new NotQuery(operand));
}

class BinaryQuery : public QueryBase
{
protected:
  Query lhs, rhs;
  std::string op_sym;
  BinaryQuery(const Query &l, const Query &r, std::string s)
      : lhs(l), rhs(r), op_sym(s) {}
  std::string rep() const { return "(" + lhs.rep() + " " + op_sym + " " + rhs.rep() + ")"; }
};

class AndQuery : public BinaryQuery
{
  friend Query operator&(const Query &, const Query &);
  AndQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "&") {}
  QueryResult eval(const TextQuery &) const;
};

inline Query operator&(const Query &lhs, const Query &rhs)
{
  return std::shared_ptr<QueryBase>(new AndQuery(lhs, rhs));
}

class OrQuery : public BinaryQuery
{
  friend Query operator|(const Query &, const Query &);
  OrQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "|") {}
  QueryResult eval(const TextQuery &) const;
};

inline Query operator|(const Query &lhs, const Query &rhs)
{
  return std::shared_ptr<QueryBase>(new OrQuery(lhs, rhs));
}

QueryResult OrQuery::eval(const TextQuery &text) const
{
  auto right = rhs.eval(text), left = lhs.eval(text);
  auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
  ret_lines->insert(right.begin(), right.end());
  return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult AndQuery::eval(const TextQuery &text) const
{
  auto left = lhs.eval(text), right = rhs.eval(text);
  auto ret_lines = std::make_shared<std::set<line_no>>();
  std::set_intersection(left.begin(), left.end(), right.begin(), right.end(),
                        std::inserter(*ret_lines, ret_lines->begin()));
}

QueryResult NotQuery::eval(const TextQuery &text) const
{
  auto result = query.eval(text);
  auto ret_lines = std::make_shared<std::set<line_no>>();
  auto beg = result.begin();
  auto end = result.end();
  auto sz = result.get_file()->size();
  for (std::size_t n = 0; n != sz; ++n)
  {
    if (beg == end || *beg != n)
    {
      ret_lines->insert(n);
    }
    else if (beg != end)
    {
      ++beg;
    }
  }
  return QueryResult(rep(), ret_lines, result.get_file());
}