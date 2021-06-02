#pragma once

#include <vector>
#include <variant>
#include <string>

#include "operation.h"

class Unit{
public:
    Unit(std::string unitString);
    ~Unit();

    float evalUnit(float x);
private:
    std::vector< std::variant<Unit, Operation, float> > parts;
};