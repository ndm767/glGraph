#pragma once

#include <GL/glew.h>

class Shader {
public:
  Shader();
  ~Shader();

  void useProgram();
  void setUniform3f(const char *name, float one, float two, float three);

private:
  GLuint shaderProgram;
};
