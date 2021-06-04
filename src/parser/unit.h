#pragma once

#include <string>
#include <variant>
#include <vector>

#include "operation.h"

class Unit {
public:
  Unit(std::string unitString);
  ~Unit();

  float evalUnit(float x);
  std::string getUnitString() { return uString; }

private:
  void performOps(std::vector<std::variant<Operation, float>> &transformed,
                  char op1, char op2);
  std::vector<std::variant<Operation, float>>
  transformUnit(std::vector<std::variant<Operation, float>> parts);
  std::vector<std::variant<Unit, Operation, float>> parts;
  std::string uString;
};
