#pragma once

#include <string>
#include <memory>
#include <map>

#include "unit.h"

class Equation{
public:
    Equation(std::string equation);
    ~Equation();

    float evalAtX(float x);

    std::map<float, float> exportRange(float startX, float endX, float resolution);
private:
    std::string origEq;

    bool isOperator(char c);
    std::string parenEq(std::string eq);

    Unit *baseUnit;
};