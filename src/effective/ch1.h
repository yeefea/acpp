#pragma once
#include <iostream>
// const 代替#define
const double ASPECT_RATIO = 1.653;
const char *const author_name = "yeefea";

class GamePlayer
{
private:
  // 类常量声明，初始值，Primer 7.6节
  // 只有static const member可以类内初始化，且必须是constexpr
  static constexpr int NUM_TURNS = 5;
  // static const int NUM_TURNS = 5;  // 和上面等价
  // 只有写了初始值才能在这里用做数组维度
  int scores[NUM_TURNS];

  static const int ci;

public:
  const int *get_scores() const { return scores; }
  
  static GamePlayer gp1; // 静态成员可以是他所属的类类型
};

// 如果要用到NUM_TURNS的地址，在类外部需要定义，并且不能再定义一个初始值！
constexpr int GamePlayer::NUM_TURNS;
const int GamePlayer::ci = 10;

// 1995年以前的语法
class OldGamePlayer
{
private:
  enum
  {
    NUM_TURNS = 5
  };
  int scores[NUM_TURNS];
};

template <typename T>
inline const T &max(const T &a, const T &b)
{
  return a > b ? a : b;
}

class Rational
{
  friend std::ostream &operator<<(std::ostream &, const Rational &);

public:
  Rational(int numerator = 0, int denominator = 1);

private:
  int n;
  int d;
};