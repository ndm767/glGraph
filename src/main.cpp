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
  // TODO: don't render lines that are completely off screen
  // TODO: change movement to be more manageable
  // TODO: make it so unit isn't completely reevaluated every time
  // TODO: improve performance at high scales

  std::vector<std::string> currEqs = {""};
  std::vector<Equation *> eqs = {new Equation("")};
  Renderer r;

  // viewport controls
  double xPos = 0.0f;
  double resolution = 0.1f;
  double scale = 1.0f;
  bool scaleRes = true;

  // misc calculator controls
  bool useDeg = false;

  while (r.isRunning()) {
    r.clear();

    bool updateEq = false;
    bool updatePos = false;

    r.update(&xPos, &scale, &currEqs, &resolution, &scaleRes, &updateEq,
             &updatePos, &useDeg);

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
          std::map<double, double> map = eqs.at(index)->exportRange(
              xPos, scale, resolution, scaleRes, useDeg);
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
