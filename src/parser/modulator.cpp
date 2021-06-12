#include "modulator.h"

#include <cmath>
#include <string>

Modulator::Modulator() { m = mod::NONE; }

Modulator::~Modulator(){};

double Modulator::applyMod(double x) {
  switch (m) {
  case mod::SIN:
    return std::sin(x);
  case mod::COS:
    return std::cos(x);
  case mod::TAN:
    return std::tan(x);
  case mod::SQRT:
    return std::sqrt(x);
  case mod::NONE:
    return x;
  default:
    return x;
  }
}

std::ostream &operator<<(std::ostream &os, const Modulator &m) {
  std::string ret = "";
  switch (m.getM()) {
  case mod::SIN:
    ret = "sin";
    break;
  case mod::COS:
    ret = "cos";
    break;
  case mod::TAN:
    ret = "tan";
    break;
  case mod::SQRT:
    ret = "sqrt";
    break;
  case mod::NONE:
    break;
  default:
    break;
  }
  return os << ret;
}
