#pragma once

#include "line.h"
#include "shader.h"

class Grid {
public:
  Grid();
  ~Grid();

  void updateGrid(double xOffset, double yOffset, double scale);
  void renderGrid(Shader *s);

private:
  std::vector<Line *> vertLines;
  std::vector<Line *> horizLines;
  Line *yAxis;
  Line *xAxis;
  bool xAct, yAct;
};
