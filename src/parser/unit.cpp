#include "unit.h"

#include <iostream>
#include <regex>

Unit::Unit(std::string unitString){
    int parenDepth = 0;
    uString = unitString;
    std::string curr = "";
    for(auto c = unitString.begin(); c<unitString.end(); c++){
        if(*c == '('){
            if(parenDepth != 0){
                curr += *c;
            }
            parenDepth++;
        }else if(*c == ')'){
            if(parenDepth > 1){
                curr += *c;
            }else{
                Unit temp(curr);
                parts.push_back(temp);
                curr = "";
            }
            parenDepth--;
        }else if(parenDepth == 0){
            switch(*c){
            case '+':
            case '-':
            case '*':
            case '/':
            case ' ':
            case '^':
                {
                    Operation temp(*c);
                    parts.push_back(temp);
                }
                break;
            default:
                curr += *c;
                break;
            }
        }else{
            curr += *c;
        }
    }
}

Unit::~Unit(){

}

void Unit::performOps(std::vector< std::variant <Operation, float> >& transformed, char op1, char op2){
    int index = 0;
    for(auto t : transformed){
        if(std::holds_alternative<Operation>(t)){
            Operation o = std::get<Operation>(t);
            if(o.getOp() == op1 || o.getOp() == op2){
                //TODO: Check if these are actually floats
                float lhs, rhs;
                lhs = std::get<float>(transformed.at(index-1));
                rhs = std::get<float>(transformed.at(index+1));
                float temp = o.performOperation(lhs, rhs);
                auto er = transformed.begin() + index - 1;
                transformed.erase(er);
                transformed.erase(er);
                transformed.erase(er);
                transformed.insert(er, temp);
            }
        }
        index++;
    }
}

float Unit::evalUnit(float x){
    //return if it is just x
    if(uString == "x"){
        return x;
    }
    
    //return if just number
    std::smatch m;
    std::regex isNum("(\\d*)(.?)(\\d*)");
    if(std::regex_match(uString, m, isNum)){
        return atof(m[0].str().c_str());
    }

    std::vector< std::variant<Operation, float> > transformed;

    for(auto p : parts){
        if(std::holds_alternative<Unit>(p)){
            transformed.push_back(std::get<Unit>(p).evalUnit(x));
        }else if(std::holds_alternative<float>(p)){
            transformed.push_back(std::get<float>(p));
        }else if(std::holds_alternative<Operation>(p)){
            transformed.push_back(std::get<Operation>(p));
        }
    }

    //return the number if it is just a number
    if(transformed.size() == 1 && std::holds_alternative<float>(transformed.at(0))){
        return std::get<float>(transformed.at(0));
    }

    performOps(transformed, '^', ' ');
    performOps(transformed, '*', '/');
    performOps(transformed, '+', '-');

    if(transformed.size() == 1){
        if(std::holds_alternative<float>(transformed.at(0))){
            return std::get<float>(transformed.at(0));
        }
    }

    return 0;
}