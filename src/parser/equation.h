#pragma once

#include <map>
#include <string>

#include "unit.h"

class Equation {
public:
  Equation(std::string eq);
  ~Equation();

  // evaluate at a single x-value
  double evalAtX(double x, bool useDeg);

  // evaluate over a range of x-values
  std::map<double, double> exportRange(double xPos, double dist,
                                       double resolution, bool scaleRes,
                                       bool useDeg);

private:
  std::string origEq;
  Unit *baseUnit;

  std::string processEq(std::string eq);

  bool isModStart(char c);
  bool isModulator(std::string t);
  bool isOperator(char c);
};
