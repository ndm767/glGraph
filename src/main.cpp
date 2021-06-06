#include <iostream>

#include "parser/equation.h"
#include "renderer/renderer.h"

int main(int argc, char *argv[]) {

  // TODO: axis labeling
  // TODO: make variable line color
  // TODO: add proper makefile
  // TODO: make it so not all equations update when you update a single equation
  // TODO: add ability to remove lines
  // TODO: add ability to put negative sign before parentheses

  std::vector<std::string> currEqs = {""};
  std::vector<Equation *> eqs = {new Equation("")};
  Renderer r;

  // viewport controls
  float xPos = 0.0f;
  float resolution = 0.1f;
  float scale = 1.0f;

  while (r.isRunning()) {
    r.clear();

    bool updateEq = false;
    bool updatePos = false;

    r.update(&xPos, &scale, &currEqs, &resolution, &updateEq, &updatePos);

    if (updateEq) {
      for (int i = 0; i < eqs.size(); i++) {
        delete eqs.at(i);
        eqs.at(i) = new Equation(currEqs.at(i));
      }
      if (currEqs.size() > eqs.size()) {
        eqs.push_back(new Equation(currEqs.at(currEqs.size() - 1)));
      }
    }

    if (updatePos) {
      int index = 0;
      for (auto s : currEqs) {
        if (s != "") {
          std::map<float, float> map =
              eqs.at(index)->exportRange(xPos, scale, resolution);
          r.graphLine(map, index);
          /*for (auto [x, y] : map) {
            std::cout << "x=" << x << " "
                      << "y=" << y << std::endl;
          }*/
        }
        index++;
      }
    }
  }

  for (int i = 0; i < eqs.size(); i++)
    delete eqs.at(i);

  return 0;
}
