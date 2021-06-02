#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"

class Renderer{
public:
    Renderer();
    ~Renderer();

    bool isRunning(){ return running; }

    void clear();
    void update();

    void graphPoint(float x, float y);
    void graphLine(std::unordered_map<int, int> points);

    bool eqShouldUpdate(){ return eqUpdate; }
    std::string exportEq(){
        if(eqUpdate){
            eqUpdate = false;
            return std::string(eqBuf);
        }else{
            return "";
        }
    }
    
private:
    bool running;
    int screenWidth = 640;
    int screenHeight = 480;

    bool eqUpdate;
    char eqBuf[512];
    float lineColor[3];

    SDL_Window *gWindow;
    SDL_GLContext gContext;
};