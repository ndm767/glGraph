#include <iostream>

#include "parser/equation.h"

int main(int argc, char *argv[]){
    std::string eq = "2x + 3 * (12 - 5)";
    Equation e(eq);

    std::cout<<"x=0: "<<e.evalAtX(0.0f)<<std::endl;
    std::cout<<"x=1: "<<e.evalAtX(1.0f)<<std::endl;
    std::cout<<"x=2: "<<e.evalAtX(2.0f)<<std::endl;

    std::string eq2 = "2^(x+1)";
    Equation e2(eq2);

    std::cout<<"x=0: "<<e2.evalAtX(0.0f)<<std::endl;
    std::cout<<"x=1: "<<e2.evalAtX(1.0f)<<std::endl;
    std::cout<<"x=2: "<<e2.evalAtX(2.0f)<<std::endl;
    
    return 0;
}