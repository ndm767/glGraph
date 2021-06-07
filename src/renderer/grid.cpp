#include "grid.h"

#include <cmath>
#include <iostream>

Grid::Grid() { updateGrid(0.0f, 0.0f, 1.0f); }

Grid::~Grid() {
  for (int i = 0; i < horizLines.size(); i++) {
    delete horizLines.at(i);
  }
  for (int i = 0; i < vertLines.size(); i++) {
    delete vertLines.at(i);
  }
}

void Grid::updateGrid(float xOffset, float yOffset, float scale) {
  horizLines.clear();
  float x = (0.0f + xOffset) / scale;
  float v[] = {x, 1.0f, 0.0f, x, -1.0f, 0.0f};
  horizLines.push_back(new Line(v, 6));

  vertLines.clear();
  float y = (0.0f + yOffset);
  float vy[] = {-1.0f, y, 0.0f, 1.0f, y, 0.0f};
  vertLines.push_back(new Line(vy, 6));
}

void Grid::renderGrid(Shader *s) {
  s->setUniform3f("color", 0.5f, 0.5f, 0.5f);
  for (auto l : vertLines) {
    l->draw();
  }
  for (auto l : horizLines) {
    l->draw();
  }
}
