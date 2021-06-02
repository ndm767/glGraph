#include <iostream>

#include "parser/equation.h"
#include "renderer/renderer.h"

int main(int argc, char *argv[]){

    //TODO: support negative numbers in equation
    //TODO: support range export in equation
    //TODO: support zoom
    //TODO: support movement
    //TODO: support undefined behavior (divide by 0, etc)

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
            std::map<float, float> r = e->exportRange(startX, endX, 0.5f);
            for(auto [x, y] : r){
                std::cout<<"x="<<x<<" "<<"y="<<y<<std::endl;
            }
        }

        r.update(&startX, &startY, &endX, &endY);
    }

    delete e;
    
    return 0;
}