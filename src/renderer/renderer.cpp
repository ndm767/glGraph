#include "renderer.h"
#include "imgui/imgui.h"

#include <iostream>

Renderer::Renderer() {
  running = true;
  lineAct = false;

  for (int i = 0; i < 512; i++)
    eqBuf[i] = 0;

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

  yOffset = 0.0f;
  xOffset = 0.0f;

  showMouse = false;

  glLineWidth(4.0f);
}

Renderer::~Renderer() {
  delete s;
  if (lineAct) {
    delete l;
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

void Renderer::update(float *xPos, float *scale, std::string *equ,
                      float *resolution, bool *updateEq, bool *updatePos) {
  s->useProgram();
  if (lineAct) {
    l->draw();
  }
  SDL_GetMouseState(&mouseX, &mouseY);

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(gWindow);
  ImGui::NewFrame();

  ImGui::Begin("Grapher");
  ImGui::Text("Enter equation: ");
  ImGui::SameLine();
  ImGui::InputTextWithHint("", "equation", eqBuf, IM_ARRAYSIZE(eqBuf));
  ImGui::Text("Resolution: ");
  ImGui::SameLine();
  ImGui::InputFloat("r", resolution);
  if (ImGui::Button("Graph")) {
    *equ = std::string(eqBuf);
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

void Renderer::graphLine(std::map<float, float> points) {
  if (lineAct) {
    delete l;
  }
  lineAct = true;

  std::vector<float> verts;

  int numPoints = points.size();
  float step = 2.0f / (numPoints - 1);

  int index = 0;
  for (auto [x, y] : points) {
    // verts.push_back(x + xOffset);
    verts.push_back(index * step - 1.0f);
    verts.push_back(y + yOffset);
    verts.push_back(0.0f);
    index++;
  }

  l = new Line(verts);
}
