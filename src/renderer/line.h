#pragma once

#include <GL/glew.h>

#include <vector>

class Line {
public:
  Line(std::vector<float> verts);
  ~Line();

  void draw();

private:
  GLuint VAO, VBO;
  std::vector<float> vertices;
};
