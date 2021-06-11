#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <vector>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"

#include "grid.h"
#include "line.h"
#include "shader.h"

class Renderer {
public:
  Renderer();
  ~Renderer();

  bool isRunning() { return running; }

  void clear();
  void update(double *xPos, double *scale, std::vector<std::string> *equs,
              double *resolution, bool *scaleRes, bool *updateEq,
              bool *updatePos);

  void graphPoint(double x, double y);
  void graphLine(std::map<double, double> points, int index, double scale);

private:
  bool running;
  int screenWidth = 1024;
  int screenHeight = 600;

  bool eqUpdate;
  std::vector<char *> eqBuf;

  double yOffset;
  double xOffset;

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
  int currSel;

  Grid *g;
};
