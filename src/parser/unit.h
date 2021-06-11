#pragma once

#include <string>
#include <variant>
#include <vector>

#include "operation.h"

class Unit {
public:
  Unit(std::string unitString);
  ~Unit();

  double evalUnit(double x);
  std::string getUnitString() { return uString; }

private:
  void performOps(std::vector<std::variant<Operation, double>> &transformed,
                  char op1, char op2);
  std::vector<std::variant<Operation, double>>
  transformUnit(std::vector<std::variant<Operation, double>> parts);
  std::vector<std::variant<Unit, Operation, double>> parts;
  std::string uString;
};
