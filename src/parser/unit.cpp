#include "unit.h"

#include <iostream>

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

float Unit::evalUnit(float x){
    std::vector< std::variant<Operation, float, std::string> > transformed;
    for(auto p : parts){
        if(std::holds_alternative<Unit>(p)){
            transformed.push_back(std::get<Unit>(p).getUnitString());
        }else if(std::holds_alternative<float>(p)){
            transformed.push_back(std::get<float>(p));
        }else if(std::holds_alternative<Operation>(p)){
            transformed.push_back(std::get<Operation>(p));
        }
    }

    for(auto t : transformed){
        if(std::holds_alternative<Operation>(t)){
            std::cout<<std::get<Operation>(t).getOp()<<" ";
        }else if(std::holds_alternative<float>(t)){
            std::cout<<std::get<float>(t)<<" ";
        }else{
            std::cout<<std::get<std::string>(t)<<" ";
        }
    }
    std::cout<<std::endl;

    return 0;
}