#include <iostream>

#include "parser/equation.h"
#include "renderer/renderer.h"

int main(int argc, char *argv[]) {

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

    // update changed equations
    if (updateEq) {
      for (int i = 0; i < std::min(currEqs.size(), eqs.size()); i++) {
        delete eqs.at(i);
        eqs.at(i) = new Equation(currEqs.at(i));
      }
      // if an equation should be removed, remove it
      if (currEqs.size() < eqs.size()) {
        delete eqs.at(eqs.size() - 1);
        eqs.erase(eqs.end() - 1);
      }
      // if an equation should be added, add it
      if (currEqs.size() > eqs.size()) {
        eqs.push_back(new Equation(currEqs.at(currEqs.size() - 1)));
      }
    }

    // redraw the equations when the camera position updates
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
