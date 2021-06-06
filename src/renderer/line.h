#pragma once

#include <GL/glew.h>

#include <vector>

class Line {
public:
  Line(std::vector<float> verts);
  ~Line();

  void draw();

  float getColorR() { return color[0]; }
  float getColorG() { return color[1]; }
  float getColorB() { return color[2]; }

  void setColor(float r, float g, float b);

private:
  GLuint VAO, VBO;
  std::vector<float> vertices;
  float color[3];
};
