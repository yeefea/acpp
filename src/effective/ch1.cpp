#include "ch1.h"

#include <cstdlib>
#include <iostream>

#include "utils.h"

void demo_const() {
  GamePlayer gp;
  auto scores = gp.get_scores();
  LOG(scores[0]);
}
void demo_template() {
  LOG(max(1, 3));
  LOG(max(9.6, 9.96));
}

Rational::Rational(int numerator, int denominator)
    : n(numerator), d(denominator) {}
std::ostream& operator<<(std::ostream& os, const Rational& r) {
  os << "Rational(" << r.n << '/' << r.d << ')';
  return os;
}

void demo_iostream() {
  Rational rat;
  LOG(rat);
}

int main(int argc, char** argv) {
  RUN_DEMO(demo_const);
  RUN_DEMO(demo_template);
  RUN_DEMO(demo_iostream);

  return EXIT_SUCCESS;
}