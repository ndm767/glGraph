#include <iostream>

#include "parser/equation.h"
#include "renderer/renderer.h"

int main(int argc, char *argv[]){

    //TODO: support zoom
    //TODO: support movement
    //TODO: support undefined behavior (divide by 0, etc)
    //TODO: axis labeling
    //TODO: allow for multiple lines

    std::string currEq = "";
    Equation *e = new Equation("");
    Renderer r;

    //viewport controls
    float startX = -1.0f;
    float endX = 1.0f;
    float resolution = 0.5f;

    while(r.isRunning()){
        r.clear();

        if(r.update(&currEq, &resolution)){
            delete e;
            e = new Equation(currEq);
            if(currEq != ""){
                std::map<float, float> map = e->exportRange(startX, endX, resolution);
                r.graphLine(map);
                /*for(auto [x, y] : map){
                    std::cout<<"x="<<x<<" "<<"y="<<y<<std::endl;
                }*/
            }
        }

    }

    delete e;
    
    return 0;
}