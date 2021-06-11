#include "line.h"

#include <iostream>

Line::Line(std::vector<double> verts) {
  vertices = verts;
  init();
}

Line::Line(double *verts, int numVerts) {
  for (int i = 0; i < numVerts; i++) {
    vertices.push_back(verts[i]);
  }
  init();
}

void Line::init() {
  color[0] = 1.0f;
  color[1] = 0.0f;
  color[2] = 0.0f;

  selected = false;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, (void *)0);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(double),
               vertices.data(), GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
}

Line::~Line() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}

void Line::draw() {
  glBindVertexArray(VAO);
  glDrawArrays(GL_LINE_STRIP, 0, vertices.size() / 3);
}

void Line::setColor(float r, float g, float b) {
  color[0] = r;
  color[1] = g;
  color[2] = b;
}
