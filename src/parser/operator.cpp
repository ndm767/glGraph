#include "operator.h"

#include <cmath>

Operator::Operator(char c) { op = c; }

Operator::~Operator() {}

double Operator::evalOp(double lhs, double rhs) {
  switch (op) {
  case '+':
    return lhs + rhs;
  case '-':
    return lhs - rhs;
  case '/':
    return lhs / rhs;
  case '*':
    return lhs * rhs;
  case '^':
    return std::pow(lhs, rhs);
  default:
    return lhs + rhs;
  }
}
