#pragma once

#define RUN_DEMO(X)                      \
  do                                     \
  {                                      \
    std::cout << ">>> " #X << std::endl; \
    X();                                 \
    std::cout << std::endl;              \
  } while (0)

#define OUTPUT_VAL(X) #X "=" << (X)

extern const int bufsize;
extern const double pi;