#pragma once

#include <iostream>

enum class mod { NONE = 0, SIN = 1, COS = 2, TAN = 3, SQRT = 4 };

class Modulator {
public:
  Modulator();
  ~Modulator();

  mod getM() const { return m; }
  void setM(mod modulator) { m = modulator; }

  double applyMod(double x);

  friend std::ostream &operator<<(std::ostream &os, const Modulator &m);

private:
  mod m;
};
