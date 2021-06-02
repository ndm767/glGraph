#pragma once

#include <string>
#include <memory>

#include "unit.h"

class Equation{
public:
    Equation(std::string equation);
    ~Equation();

    float evalAtX(float x);
private:
    std::string origEq;

    bool isOperator(char c);
    std::string parenEq(std::string eq);

    Unit *baseUnit;
};