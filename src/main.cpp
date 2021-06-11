#include <iostream>

#include "parser/equation.h"
#include "renderer/renderer.h"

int main(int argc, char *argv[]) {

  // TODO: axis labeling
  // TODO: axis grid
  // TODO: add ability to specify screen dimensions
  // TODO: add proper makefile
  // TODO: make it so not all equations update when you update a single equation
  // TODO: add ability to remove lines
  // TODO: add ability to put negative sign before parentheses
  // TODO: add implied multiplication to parentheses
  // TODO: add square root function
  // TODO: add trigonometric functions
  // TODO: add logarithms
  // TODO: add "solve for x" type equations (like circle equations) a.k.a add
  // support for "=" sign
  // TODO: add variable movement speed
  // TODO: don't render lines that are completely off screen
  // TODO: investigate using compute shader
  // TODO: change movement to be more manageable

  std::vector<std::string> currEqs = {""};
  std::vector<Equation *> eqs = {new Equation("")};
  Renderer r;

  // viewport controls
  double xPos = 0.0f;
  double resolution = 0.1f;
  double scale = 1.0f;
  bool scaleRes = true;

  while (r.isRunning()) {
    r.clear();

    bool updateEq = false;
    bool updatePos = false;

    r.update(&xPos, &scale, &currEqs, &resolution, &scaleRes, &updateEq,
             &updatePos);

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
          std::map<double, double> map =
              eqs.at(index)->exportRange(xPos, scale, resolution, scaleRes);
          r.graphLine(map, index, scale);
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
