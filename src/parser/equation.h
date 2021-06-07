#pragma once

#include <map>
#include <memory>
#include <string>

#include "unit.h"

class Equation {
public:
  Equation(std::string equation);
  ~Equation();

  float evalAtX(float x);

  std::map<float, float> exportRange(float xPos, float dist, float resolution,
                                     bool scaleRes);

private:
  std::string origEq;

  bool isOperator(char c);
  std::string parenEq(std::string eq);

  Unit *baseUnit;
};
