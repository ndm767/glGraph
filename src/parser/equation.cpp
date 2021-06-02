#include "equation.h"

#include <iostream>

Equation::Equation(std::string equation){
    origEq = parenEq(equation);
    std::cout<<"Original: "<<equation<<std::endl;
    std::cout<<"Paren'd: "<<origEq<<std::endl;
}

Equation::~Equation(){

}

bool Equation::isOperator(char c){
    switch(c){
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case ' ':
    case '^':
        return true;
    default:
        return false;
    }
}

std::string Equation::parenEq(std::string eq){
    std::string ret = "";

    //go through and surround all numbers and variables with parenthesis
    auto it = eq.begin();
    std::string curr = "";
    for(; it < eq.end(); it++){
        if(!isOperator(*it)){
            curr += *it;
        }else{
            if(curr != ""){
                ret += "(" + curr + ")";
                curr = "";
            }
            ret += *it;
        }
    }

    return ret;
}