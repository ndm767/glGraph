#include "operation.h"

#include <cmath>

Operation::Operation(char op){
    this->op = op;
}

Operation::~Operation(){

}

float Operation::performOperation(float lhs, float rhs){
    switch(op){
        case '+':
            return lhs + rhs;
        case '-':
            return lhs - rhs;
        case '*':
            return lhs * rhs;
        case '/':
            return lhs/rhs;
        case '^':
            return pow(lhs, rhs);
        default:
            return 0.0f;
    }
}