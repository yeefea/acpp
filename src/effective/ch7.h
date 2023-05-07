#pragma once

// 48 TMP
template <unsigned N>
struct Factorial
{
  enum
  {
    value = N * Factorial<N - 1>::value
  };
};

template <> // 模板特例化
struct Factorial<0>
{
  enum
  {
    value = 1
  };
};

template <int A, int B>
struct Add
{
  static const int value = A + B;
};