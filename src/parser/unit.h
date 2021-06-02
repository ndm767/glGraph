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
    std::string getUnitString(){
        return uString;
    }
private:
    std::vector< std::variant<Unit, Operation, float> > parts;
    std::string uString;
};