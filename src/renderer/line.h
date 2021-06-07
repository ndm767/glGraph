#pragma once

#include <GL/glew.h>

#include <vector>

class Line {
public:
  Line(std::vector<float> verts);
  Line(float *verts, int numVerts);
  ~Line();

  void draw();

  float getColorR() { return color[0]; }
  float getColorG() { return color[1]; }
  float getColorB() { return color[2]; }

  void setColor(float r, float g, float b);

  bool isSelected() { return selected; }
  void setSelected(bool val) { selected = val; }

private:
  void init();

  GLuint VAO, VBO;
  std::vector<float> vertices;
  float color[3];
  bool selected;
};
