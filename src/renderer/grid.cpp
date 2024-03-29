#include "grid.h"

#include <cmath>
#include <iostream>

Grid::Grid() {
  xAct = false;
  yAct = false;
  updateGrid(0.0f, 0.0f, 1.0f);
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

void Grid::updateGrid(double xOffset, double yOffset, double scale) {
  for (int i = 0; i < horizLines.size(); i++) {
    delete horizLines.at(i);
  }
  horizLines.clear();
  for (float i = yOffset; i <= scale + yOffset; i += 1.0f / scale) {
    std::vector<double> tVerts = {-1.0f, i, 0.0f, 1.0f, i, 0.0f};
    horizLines.push_back(new Line(tVerts));
  }

  for (float i = yOffset; i >= -1.0f * scale + yOffset; i -= 1.0f / scale) {
    std::vector<double> tVerts = {-1.0f, i, 0.0f, 1.0f, i, 0.0f};
    horizLines.push_back(new Line(tVerts));
  }

  if (xAct)
    delete xAxis;
  double x = (0.0f + xOffset) / scale;
  double v[] = {x, 1.0f, 0.0f, x, -1.0f, 0.0f};
  xAxis = new Line(v, 6);
  xAct = true;

  for (int i = 0; i < vertLines.size(); i++) {
    delete vertLines.at(i);
  }
  vertLines.clear();

  for (float i = xOffset / scale; i <= scale + xOffset; i += 1.0f / scale) {
    std::vector<double> tVerts = {i, -1.0f, 0.0f, i, 1.0f, 0.0f};
    vertLines.push_back(new Line(tVerts));
  }
  for (float i = xOffset / scale; i >= -1.0 * scale + xOffset;
       i -= 1.0f / scale) {
    std::vector<double> tVerts = {i, -1.0f, 0.0f, i, 1.0f, 0.0f};
    vertLines.push_back(new Line(tVerts));
  }

  if (yAct)
    delete yAxis;
  double y = (0.0f + yOffset);
  double vy[] = {-1.0f, y, 0.0f, 1.0f, y, 0.0f};
  yAxis = new Line(vy, 6);
  yAct = true;
}

void Grid::renderGrid(Shader *s) {
  s->setUniform3f("color", 0.5f, 0.5f, 0.5f);
  glLineWidth(1.0f);
  for (auto l : vertLines) {
    l->draw();
  }
  for (auto l : horizLines) {
    l->draw();
  }

  glLineWidth(4.0f);
  s->setUniform3f("color", 0.0f, 0.0f, 0.0f);
  yAxis->draw();
  xAxis->draw();
}
