#pragma once

class Operator {
public:
  Operator(char c);
  ~Operator();

  // get the type of the operator
  char getOp() { return op; }

  // evaluate an operator expression
  double evalOp(double lhs, double rhs);

private:
  // operator type
  char op;
};
