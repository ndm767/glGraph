#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <map>
#include <string>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"

#include "line.h"
#include "shader.h"

class Renderer {
public:
  Renderer();
  ~Renderer();

  bool isRunning() { return running; }

  void clear();
  void update(float *xPos, float *scale, std::string *equ, float *resolution,
              bool *updateEq, bool *updatePos);

  void graphPoint(float x, float y);
  void graphLine(std::map<float, float> points);

private:
  bool running;
  int screenWidth = 640;
  int screenHeight = 480;

  bool eqUpdate;
  char eqBuf[512];

  float yOffset;
  float xOffset;

  int mouseX, mouseY;
  bool showMouse;

  SDL_Window *gWindow;
  SDL_GLContext gContext;

  Shader *s;
  Line *l;
  bool lineAct;
};
