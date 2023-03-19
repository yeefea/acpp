#include "query_result.h"

std::ostream &print_query_result(std::ostream &os, const QueryResult &qr)
{

  os << "\"" << qr.sought << "\" occurrs " << qr.lines->size() << " time(s)" << std::endl;
  for (auto num : *qr.lines) // 等价于 *(qr.lines)
  {
    os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
  }
  return os;
}