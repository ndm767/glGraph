#include <iostream>

#include "parser/equation.h"
#include "renderer/renderer.h"

int main(int argc, char *argv[]) {

  // TODO: support undefined behavior (divide by 0, etc)
  // TODO: axis labeling
  // TODO: allow for multiple lines
  // TODO: make variable line color
  // TODO: make resolution change with scale

  std::string currEq = "";
  Equation *e = new Equation("");
  Renderer r;

  // viewport controls
  float xPos = 0.0f;
  float resolution = 0.1f;
  float scale = 1.0f;

  while (r.isRunning()) {
    r.clear();

    bool updateEq = false;
    bool updatePos = false;

    r.update(&xPos, &scale, &currEq, &resolution, &updateEq, &updatePos);

    if (updateEq) {
      delete e;
      e = new Equation(currEq);
    }

    if (updatePos) {
      if (currEq != "") {
        std::map<float, float> map = e->exportRange(xPos, scale, resolution);
        r.graphLine(map);
        /*for (auto [x, y] : map) {
          std::cout << "x=" << x << " "
                    << "y=" << y << std::endl;
        }*/
      }
    }
  }

  delete e;

  return 0;
}
