#include "number.h"

#include <cmath>
#include <iostream>

Number::Number() {
  whole = 0;
  dec = 0;
}

Number::Number(int wholeComponent, int decComponent) {
  whole = wholeComponent;
  dec = decComponent;
}

Number::Number(float number) {
  double wp, dp;
  dp = modf(number, &wp);
  whole = int(wp);
  std::string dpStr = std::to_string(dp);
  dpStr = dpStr.substr(2, dpStr.length());
  std::cout << dpStr << std::endl;
  for (auto c : dpStr) {
    dp *= 10;
  }
  dec = int(dp);
  // remove trailing zeroes
  while (dec % 10 == 0 && dec != 0) {
    dec /= 10;
  }
  std::cout << "float: " << number << " " << whole << "." << dec << std::endl;
}

Number::~Number() {}

float Number::getAsFloat() {
  float ret = float(whole);
  int decCpy = dec;
  int digits = 0;
  while (decCpy != 0) {
    decCpy = (decCpy - decCpy % 10) / 10;
    digits++;
  }
  ret += float(dec) / pow(10, digits);

  return ret;
}
