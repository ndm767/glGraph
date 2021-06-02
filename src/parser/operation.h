#pragma once

#include <string>

class Operation{
public:
    Operation(char op);
    ~Operation();
    float performOperation(float lhs, float rhs);
    char getOp(){
        return op;
    }
private:
    char op;
};