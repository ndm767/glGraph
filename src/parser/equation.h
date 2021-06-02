#pragma once

#include <string>
#include <memory>

class Equation{
public:
    Equation(std::string equation);
    ~Equation();

    std::string parenEq(std::string eq);
private:
    std::string origEq;

    bool isOperator(char c);
};