#include "renderer.h"

#include <iostream>

Renderer::Renderer(){
    running = true;

    for(int i = 0; i<512; i++)
        eqBuf[i] = 0;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    gWindow = SDL_CreateWindow("glGraph", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    gContext = SDL_GL_CreateContext(gWindow);
    SDL_GL_MakeCurrent(gWindow, gContext);

    glewExperimental = true;
    glewInit();

    //Imgui stuff
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(gWindow, gContext);
    ImGui_ImplOpenGL3_Init();
}

Renderer::~Renderer(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gContext);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void Renderer::clear(){
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::update(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(gWindow);
    ImGui::NewFrame();

    ImGui::Begin("Grapher");
    ImGui::Text("Enter equation: ");
    ImGui::SameLine();
    ImGui::InputTextWithHint("", "equation", eqBuf, IM_ARRAYSIZE(eqBuf));
    if(ImGui::Button("Graph")){
        std::cout<<eqBuf<<std::endl;
    }
    ImGui::ColorEdit3("Line Color", lineColor);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(gWindow);

    SDL_Event e;
    while(SDL_PollEvent(&e)){
        ImGui_ImplSDL2_ProcessEvent(&e);
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