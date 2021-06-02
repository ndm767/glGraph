#include "equation.h"
#include "unit.h"

#include <iostream>

Equation::Equation(std::string equation){
    origEq = parenEq(equation);
    std::cout<<"Original: "<<equation<<std::endl;
    std::cout<<"Paren'd: "<<origEq<<std::endl;
    baseUnit = new Unit(origEq);
}

Equation::~Equation(){
    delete baseUnit;
}

float Equation::evalAtX(float x){
    return baseUnit->evalUnit(x);
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
    //go through and surround all numbers and variables with parenthesis
    std::string stepOneOut = "";
    std::string curr = "";
    for(auto it = eq.begin(); it < eq.end(); it++){
        //x can only ever be by itself
        if(*it == 'x'){
            if(curr != ""){
                stepOneOut += "(" + curr + ")";
                curr = "";
            }
            stepOneOut += "(x)";

        }else if(!isOperator(*it)){
            curr += *it;
        }else{
            if(curr != ""){
                stepOneOut += "(" + curr + ")";
                curr = "";
            }
            stepOneOut += *it;
        }
    }
    //catch potential last unit and clear curr for reuse    
    if(curr != ""){
        stepOneOut += "(" + curr + ")";
        curr = "";
    }

    //add multiplication signs for implied multiplication
    char last = -1;
    curr = "";
    std::string stepTwoOut = "";
    for(auto it = stepOneOut.begin(); it < stepOneOut.end(); it++){

        if(*it != '('){
            last = *it;
        }else if(last == ')'){
            stepTwoOut += curr;
            stepTwoOut += "*";
            curr = "";
        }
        curr += *it;
    }
    if(curr != ""){
        stepTwoOut += curr;
        curr = "";
    }

    //remove spaces
    std::string stepThreeOut = "";
    for(auto it = stepTwoOut.begin(); it < stepTwoOut.end(); it++){
        if(*it != ' '){
            stepThreeOut += *it;
        }
    }
    return stepThreeOut;
}

std::map<float, float> Equation::exportRange(float startX, float endX, float resolution){
    std::map<float, float> ret;
    for(float i = startX; i < endX + resolution; i += resolution){
        ret[i] = evalAtX(i);
    }
    return ret;
}