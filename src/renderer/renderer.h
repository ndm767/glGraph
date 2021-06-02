#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <unordered_map>

class Renderer{
public:
    Renderer();
    ~Renderer();

    bool isRunning(){ return running; }

    void clear();
    void update();

    void graphPoint(float x, float y);
    void graphLine(std::unordered_map<int, int> points);
private:
    bool running;
    int screenWidth = 640;
    int screenHeight = 480;

    SDL_Window *gWindow;
    SDL_GLContext gContext;
};