#pragma once

#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "modulator.h"
#include "operator.h"

class Unit {
public:
  Unit(std::string eq);
  ~Unit();

  // evaluate the unit at an x-value
  // and choose whether or not to use degrees (for trigonometric functions)
  double evalUnit(double x, bool useDeg);

  std::string getEqStr() { return eqStr; }

private:
  std::string eqStr;
  bool hasVar;
  double noVarValDeg;
  double noVarValRad;

  bool modExp;
  Modulator m;
  std::pair<Modulator, Unit *> modUnit;

  bool isOperator(char c);
  std::vector<std::variant<double, Operator, Unit>> exp;

  // evaluate operator expressions
  double evalOps(std::vector<std::variant<double, Operator>> opVec);
};
