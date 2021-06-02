#include "renderer.h"

Renderer::Renderer(){
    running = true;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    gWindow = SDL_CreateWindow("glGraph", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    gContext = SDL_GL_CreateContext(gWindow);
    SDL_GL_MakeCurrent(gWindow, gContext);

    glewExperimental = true;
    glewInit();
}

Renderer::~Renderer(){
    SDL_GL_DeleteContext(gContext);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void Renderer::clear(){
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::update(){
    SDL_GL_SwapWindow(gWindow);

    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            running = false;
        }else if(e.type == SDL_KEYDOWN){
            if(e.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
                running = false;
            }
        }
    }
}

void Renderer::graphPoint(float x, float y){

}

void Renderer::graphLine(std::unordered_map<int, int> points){

}