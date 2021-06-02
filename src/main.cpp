#include <iostream>

#include "parser/equation.h"
#include "renderer/renderer.h"

int main(int argc, char *argv[]){

    //TODO: support negative numbers in equation
    //TODO: support range export in equation
    //TODO: support zoom
    //TODO: support movement

    Equation *e = new Equation("");
    Renderer r;

    //viewport controls
    float startX = -1.0f;
    float endX = 1.0f;
    float startY = -1.0f;
    float endY = 1.0f;

    while(r.isRunning()){
        r.clear();
        if(r.eqShouldUpdate()){
            delete e;
            e = new Equation(r.exportEq());
            std::cout<<"x=0: "<<e->evalAtX(0.0f)<<std::endl;
        }

        r.update(&startX, &startY, &endX, &endY);
    }

    delete e;
    
    return 0;
}