#pragma once

class Operator {
public:
  Operator(char c);
  ~Operator();

  char getOp() { return op; }

  double evalOp(double lhs, double rhs);

private:
  char op;
};
