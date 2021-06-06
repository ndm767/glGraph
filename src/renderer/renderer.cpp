#include "renderer.h"
#include "imgui/imgui.h"

#include <iostream>

Renderer::Renderer() {
  running = true;
  lineAct = false;

  eqUpdate = false;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  gWindow = SDL_CreateWindow("glGraph", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight,
                             SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
  gContext = SDL_GL_CreateContext(gWindow);
  SDL_GL_MakeCurrent(gWindow, gContext);

  glewExperimental = true;
  glewInit();

  // Imgui stuff
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  ImGui::StyleColorsDark();

  ImGui_ImplSDL2_InitForOpenGL(gWindow, gContext);
  ImGui_ImplOpenGL3_Init();

  s = new Shader();

  numLines = 1;
  eqBuf.push_back(new char[512]);
  for (int i = 0; i < 512; i++) {
    *(eqBuf.at(0) + i) = 0;
  }
  yOffset = 0.0f;
  xOffset = 0.0f;

  showMouse = false;

  glLineWidth(4.0f);
}

Renderer::~Renderer() {
  delete s;
  if (lineAct) {
    for (int i = 0; i < lines.size(); i++) {
      delete lines.at(i);
    }
  }
  for (int i = 0; i < eqBuf.size(); i++) {
    delete[] eqBuf.at(i);
  }
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_GL_DeleteContext(gContext);
  SDL_DestroyWindow(gWindow);
  SDL_Quit();
}

void Renderer::clear() {
  glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::update(float *xPos, float *scale, std::vector<std::string> *equs,
                      float *resolution, bool *updateEq, bool *updatePos) {
  s->useProgram();
  if (lineAct) {
    for (auto l : lines) {
      l->draw();
    }
  }
  SDL_GetMouseState(&mouseX, &mouseY);

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(gWindow);
  ImGui::NewFrame();

  ImGui::Begin("Grapher");
  ImGui::Text("Resolution: ");
  ImGui::SameLine();
  ImGui::InputFloat("r", resolution);
  ImGui::Text("Enter equations: ");
  for (int i = 0; i < numLines; i++) {
    ImGui::InputTextWithHint(std::to_string(i).c_str(), "equation", eqBuf.at(i),
                             512);
  }

  if (ImGui::Button("Add line")) {
    eqBuf.push_back(new char[512]);
    for (int i = 0; i < 512; i++) {
      *(eqBuf.at(eqBuf.size() - 1) + i) = 0;
    }
    equs->push_back("");
    numLines++;
  }
  ImGui::SameLine();
  if (ImGui::Button("Graph")) {
    for (int i = 0; i < eqBuf.size(); i++) {
      equs->at(i) = std::string(eqBuf.at(i));
    }
    *updateEq = true;
    *updatePos = true;
  }
  ImGui::Text("Camera Y: %f", -1.0f * yOffset);
  ImGui::Text("Camera X: %f", -1.0f * xOffset);
  ImGui::Text("Scale: %f", *scale);
  ImGui::Checkbox("Show mouse position", &showMouse);
  if (showMouse) {
    ImGui::Text("Mouse: (%f, %f)",
                float(mouseX / float(screenWidth / 2.0f) - 1.0f) - xOffset,
                float(-1.0f * (mouseY) / float(screenHeight / 2.0f) + 1.0f) -
                    yOffset);
  }
  ImGui::End();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  SDL_GL_SwapWindow(gWindow);

  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    ImGui_ImplSDL2_ProcessEvent(&e);
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
        running = false;
      } else {

        switch (e.key.keysym.scancode) {
        case SDL_SCANCODE_W:
          *updatePos = true;
          yOffset -= 0.1f;
          break;
        case SDL_SCANCODE_S:
          *updatePos = true;
          yOffset += 0.1f;
          break;
        case SDL_SCANCODE_A:
          *updatePos = true;
          *xPos -= 0.1f;
          xOffset += 0.1f;
          break;
        case SDL_SCANCODE_D:
          *updatePos = true;
          *xPos += 0.1f;
          xOffset -= 0.1f;
          break;
        case SDL_SCANCODE_Q:
          *updatePos = true;
          *scale *= 1.1f;
          break;
        case SDL_SCANCODE_E:
          *updatePos = true;
          *scale /= 1.1f;
          break;
        default:
          break;
        }
      }
    }
  }
  if (*scale <= 0.0f) {
    *scale = 0.1f;
  }
}

void Renderer::graphPoint(float x, float y) {}

void Renderer::graphLine(std::map<float, float> points, int index) {
  if (lineAct && index < lines.size()) {
    delete lines.at(index);
  }
  lineAct = true;

  std::vector<float> verts;

  int numPoints = points.size();
  float step = 2.0f / (numPoints - 1);

  int i = 0;
  for (auto [x, y] : points) {
    // verts.push_back(x + xOffset);
    verts.push_back(i * step - 1.0f);
    verts.push_back(y + yOffset);
    verts.push_back(0.0f);
    i++;
  }
  if (index < lines.size()) {
    lines.at(index) = new Line(verts);
  } else {
    lines.push_back(new Line(verts));
  }
}
