#pragma once

#include <GL/glew.h>

class Shader {
public:
  Shader();
  ~Shader();

  void useProgram();
  void setUniform3f(const char *name, float one, float two, float three);
  void setUniform1f(const char *name, float val);

private:
  GLuint shaderProgram;
};
