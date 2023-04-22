#pragma once
#include <iostream>
// const 代替#define
const double ASPECT_RATIO = 1.653;
const char* const author_name = "yeefea";

class GamePlayer {
 private:
  // static const member
  static const int NUM_TURNS = 5;
  int scores[NUM_TURNS];

 public:
  const int* get_scores() const { return scores; }
};

// 1995年以前的语法
class OldGamePlayer {
 private:
  enum { NUM_TURNS = 5 };
  int scores[NUM_TURNS];
};

template <typename T>
inline const T& max(const T& a, const T& b) {
  return a > b ? a : b;
}

class Rational {
  friend std::ostream& operator<<(std::ostream&, const Rational&);

 public:
  Rational(int numerator = 0, int denominator = 1);

 private:
  int n;
  int d;
};