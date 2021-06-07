#include "shader.h"

#include <iostream>

Shader::Shader() {
  const char *vertSrc = R""(
        #version 330 core
        in vec3 fPos;
        void main(){
            gl_Position = vec4(fPos, 1.0);
        }
    )"";

  const char *fragSrc = R""(
        #version 330 core
        out vec4 outColor;
	uniform vec3 color;
	uniform float opacity;
        void main(){
            outColor = vec4(color, opacity);
        }
    )"";

  int success;
  char infoLog[512];

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertSrc, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "Vertex: " << infoLog << std::endl;
  }

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragSrc, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "Fragment: " << infoLog << std::endl;
  }

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "Program: " << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

Shader::~Shader() { glDeleteProgram(shaderProgram); }

void Shader::useProgram() { glUseProgram(shaderProgram); }

void Shader::setUniform3f(const char *name, float one, float two, float three) {
  GLuint loc = glGetUniformLocation(shaderProgram, name);
  glUniform3f(loc, one, two, three);
}

void Shader::setUniform1f(const char *name, float val) {
  GLuint loc = glGetUniformLocation(shaderProgram, name);
  glUniform1f(loc, val);
}
