#pragma once

#include <map>
#include <memory>
#include <string>

#include "unit.h"

class Equation {
public:
  Equation(std::string equation);
  ~Equation();

  double evalAtX(double x);

  std::map<double, double> exportRange(double xPos, double dist,
                                       double resolution, bool scaleRes);

private:
  std::string origEq;

  bool isOperator(char c);
  std::string parenEq(std::string eq);

  Unit *baseUnit;
};
