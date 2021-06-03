#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <map>
#include <string>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"

#include "shader.h"
#include "line.h"

class Renderer{
public:
    Renderer();
    ~Renderer();

    bool isRunning(){ return running; }

    void clear();
    bool update(std::string *equ);

    void graphPoint(float x, float y);
    void graphLine(std::map<float, float> points);

private:
    bool running;
    int screenWidth = 640;
    int screenHeight = 480;

    bool eqUpdate;
    char eqBuf[512];

    float resolution;
    float yOffset;
    float xOffset;

    SDL_Window *gWindow;
    SDL_GLContext gContext;

    Shader *s;
    Line *l;
    bool lineAct;
};