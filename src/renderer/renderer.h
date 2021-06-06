#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <vector>

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
  void update(float *xPos, float *scale, std::vector<std::string> *equs,
              float *resolution, bool *updateEq, bool *updatePos);

  void graphPoint(float x, float y);
  void graphLine(std::map<float, float> points, int index);

private:
  bool running;
  int screenWidth = 640;
  int screenHeight = 480;

  bool eqUpdate;
  std::vector<char *> eqBuf;

  float yOffset;
  float xOffset;

  int mouseX, mouseY;
  bool showMouse;

  SDL_Window *gWindow;
  SDL_GLContext gContext;

  Shader *s;
  std::vector<Line *> lines;
  bool lineAct;
  int numLines;
  float newColor[3];
  int lInd;
};
