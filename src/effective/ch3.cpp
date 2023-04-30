
#include "ch3.h"

#include <cstdlib>
#include <cstring>
#include "utils.h"

Str::Str(const char *value)
{
  if (value)
  {
    data = new char[strlen(value) + 1];
    strcpy(data, value);
    data[strlen(value)] = '\0';
  }
  else
  {
    data = new char[1];
    *data = '\0';
  }
}

Str::Str(const Str &rhs)
{
  data = new char[strlen(rhs.data) + 1];
  strcpy(data, rhs.data);
  data[strlen(rhs.data)] = '\0';
}

Str &Str::operator=(const Str &rhs)
{
  delete[] data; // release existing memory
  data = new char[strlen(rhs.data) + 1];
  strcpy(data, rhs.data);
  data[strlen(rhs.data)] = '\0';
}

inline Str::~Str()
{
  delete[] data;
}

void demo_dynamic_memory()
{
}

int main()
{
  RUN_DEMO(demo_dynamic_memory);

  return EXIT_SUCCESS;
}