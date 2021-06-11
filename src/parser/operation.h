#pragma once

#include <string>

class Operation {
public:
  Operation(char op);
  ~Operation();
  double performOperation(double lhs, double rhs);
  char getOp() { return op; }

private:
  char op;
};
