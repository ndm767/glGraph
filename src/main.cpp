#include <iostream>

#include "parser/equation.h"
#include "renderer/renderer.h"

int main(int argc, char *argv[]){

    //TODO: support negative numbers in equation
    //TODO: support range export in equation
    //TODO: support zoom
    //TODO: support movement
    //TODO: support undefined behavior (divide by 0, etc)
    //TODO: Actually make the thing graph
    //TODO: axis labeling
    
    std::string currEq = "";
    Equation *e = new Equation("");
    Renderer r;

    //viewport controls
    float startX = 0.0f;
    float endX = 2.0f;
    float startY = -1.0f;
    float endY = 1.0f;
    float resolution = 0.5f;

    while(r.isRunning()){
        r.clear();

        if(r.update(&startX, &startY, &endX, &endY, &resolution, &currEq)){
            delete e;
            e = new Equation(currEq);
            std::map<float, float> r = e->exportRange(startX, endX, resolution);
            for(auto [x, y] : r){
                std::cout<<"x="<<x<<" "<<"y="<<y<<std::endl;
            }
        }

    }

    delete e;
    
    return 0;
}