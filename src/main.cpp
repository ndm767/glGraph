#include <iostream>

#include "parser/equation.h"
#include "renderer/renderer.h"

int main(int argc, char *argv[]){

    //TODO: support negative numbers in equation

    Equation *e = new Equation("");
    Renderer r;

    while(r.isRunning()){
        r.clear();
        if(r.eqShouldUpdate()){
            delete e;
            e = new Equation(r.exportEq());
            std::cout<<"x=0: "<<e->evalAtX(0.0f)<<std::endl;
        }
        r.update();
    }

    delete e;
    
    return 0;
}