#include "line.h"

Line::Line(std::vector<float> verts) {
  vertices = verts;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
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
