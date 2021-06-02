#pragma once

#include <string>

class Operation{
public:
    Operation(std::string op);
    ~Operation();
    float performOperation(float lhs, float rhs);
    std::string getOp(){
        return op;
    }
private:
    std::string op;
};