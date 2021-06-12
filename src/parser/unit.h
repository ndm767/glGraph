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

  double evalUnit(double x);

  std::string getEqStr() { return eqStr; }

private:
  std::string eqStr;

  bool modExp;
  Modulator m;
  std::pair<Modulator, Unit *> modUnit;

  bool isOperator(char c);
  std::vector<std::variant<double, Operator, Unit>> exp;

  double evalOps(std::vector<std::variant<double, Operator>> opVec);
};
