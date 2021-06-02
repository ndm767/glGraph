#include "unit.h"

#include <iostream>

Unit::Unit(std::string unitString){
    
}

Unit::~Unit(){

}

float Unit::evalUnit(float x){
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

    for(auto t : transformed){
        if(std::holds_alternative<Operation>(t)){
            std::cout<<std::get<Operation>(t).getOp()<<" ";
        }else{
            std::cout<<std::get<float>(t)<<" ";
        }
    }
    std::cout<<std::endl;

    return 0;
}