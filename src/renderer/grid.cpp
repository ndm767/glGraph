#include "grid.h"

#include <cmath>
#include <iostream>

Grid::Grid() {
  updateGrid(0.0f, 0.0f, 1.0f);
  xAct = false;
  yAct = false;
}

Grid::~Grid() {
  delete yAxis;
  delete xAxis;
  for (int i = 0; i < horizLines.size(); i++) {
    delete horizLines.at(i);
  }
  for (int i = 0; i < vertLines.size(); i++) {
    delete vertLines.at(i);
  }
}

void Grid::updateGrid(float xOffset, float yOffset, float scale) {
  horizLines.clear();
  if (xAct)
    delete xAxis;
  float x = (0.0f + xOffset) / scale;
  float v[] = {x, 1.0f, 0.0f, x, -1.0f, 0.0f};
  xAxis = new Line(v, 6);
  xAct = true;
  // horizLines.push_back(new Line(v, 6));

  vertLines.clear();
  if (yAct)
    delete yAxis;
  float y = (0.0f + yOffset);
  float vy[] = {-1.0f, y, 0.0f, 1.0f, y, 0.0f};
  yAxis = new Line(vy, 6);
  yAct = true;
  // vertLines.push_back(new Line(vy, 6));
}

void Grid::renderGrid(Shader *s) {
  s->setUniform3f("color", 0.5f, 0.5f, 0.5f);
  for (auto l : vertLines) {
    l->draw();
  }
  for (auto l : horizLines) {
    l->draw();
  }

  s->setUniform3f("color", 0.0f, 0.0f, 0.0f);
  yAxis->draw();
  xAxis->draw();
}
