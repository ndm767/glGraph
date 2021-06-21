#pragma once

#include <iostream>

enum class mod { NONE = 0, SIN = 1, COS = 2, TAN = 3, SQRT = 4 };

class Modulator {
public:
  Modulator();
  ~Modulator();

  // get and set type
  mod getM() const { return m; }
  void setM(mod modulator) { m = modulator; }

  // apply the function
  double applyMod(double x);

  // allow printing of the modulator (mostly for debug purposes)
  friend std::ostream &operator<<(std::ostream &os, const Modulator &m);

private:
  // type of modulator
  mod m;
};
