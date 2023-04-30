#pragma once

class Str{
public:
  Str(const char* value);
  Str(const Str&);
  Str& operator=(const Str&);
  ~Str();
private:
  char* data;
};

