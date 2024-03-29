#include "equation.h"

#include <algorithm>
#include <cmath>
#include <iostream>

Equation::Equation(std::string eq) {
  // std::cout << "Original: " << eq << std::endl;
  origEq = processEq(eq);
  // std::cout << "Processed: " << origEq << std::endl;

  baseUnit = new Unit(origEq);
}

Equation::~Equation() { delete baseUnit; }

// is the char the start of a function (sqrt, sin, cos, tan)
bool Equation::isModStart(char c) {
  switch (c) {
  case 's':
  case 'c':
  case 't':
    return true;
  default:
    return false;
  }
}

// is the string a function (sqrt, sin, cos, tan)
bool Equation::isModulator(std::string t) {
  if (t.length() == 3) {
    if (t.compare("sin") == 0 || t.compare("cos") == 0 ||
        t.compare("tan") == 0) {
      return true;
    }
  } else if (t.length() == 4) {
    if (t.compare("sqrt") == 0) {
      return true;
    }
  }
  return false;
}

// is the char an operator (space is counted as an operator here because spaces
// have not been removed yet when this function is used
bool Equation::isOperator(char c) {
  switch (c) {
  case '+':
  case '-':
  case '/':
  case '*':
  case '^':
  case ' ':
    return true;
  default:
    return false;
  }
}

// process the equation into something that the computer can understand
std::string Equation::processEq(std::string eq) {
  // split equation into units and surround with parentheses
  // what is a unit?
  //	number: 3.5, 5
  //	variable: x, y
  //	modulator expression: sin(x), sin(x+2), cos(3)
  std::string stepOneOut = "";
  std::string curr = "";
  std::vector<int> exitDepths;
  bool inMod = false;
  int parenDepth = 0;
  for (auto it = eq.begin(); it < eq.end(); it++) {
    if (isOperator(*it)) {
      if (curr != "") {
        stepOneOut += "(" + curr + ")";
        curr = "";
      }
      stepOneOut += *it;
    } else if (isModStart(*it)) {
      std::string test = "";
      test += *it;
      test += *(it + 1);
      test += *(it + 2);
      if (isModulator(test)) {
        if (curr != "") {
          stepOneOut += "(" + curr + ")";
          curr = "";
        }
        stepOneOut += "(" + test + "(";
        exitDepths.push_back(parenDepth);
        inMod = true;
        it += 2;
      } else {
        test += *(it + 3);
        if (isModulator(test)) {
          if (curr != "") {
            stepOneOut += "(" + curr + ")";
            curr = "";
          }

          stepOneOut += "(" + test;
          exitDepths.push_back(parenDepth);
          inMod = true;
          it += 3;
        } else {
          return "";
        }
      }
    } else if (*it == 'x' || *it == 'y') {
      if (curr != "") {
        stepOneOut += "(" + curr + ")";
        curr = "";
      }
      stepOneOut += "(";
      stepOneOut += *it;
      stepOneOut += ")";
    } else if (*it == '(') {
      parenDepth++;
      if (curr != "") {
        curr += "(";
      } else {
        stepOneOut += "(";
      }
    } else if (*it == ')') {
      parenDepth--;
      if (curr != "") {
        curr += ")";
      } else {
        stepOneOut += ")";
      }
    } else {
      curr += *it;
    }

    // deal with units inside of a modulator
    if (inMod && exitDepths.size() > 0 && *(it + 1) != '(') {
      auto f = std::find(exitDepths.begin(), exitDepths.end(), parenDepth);
      if (f != exitDepths.end()) {
        if (curr != "") {
          stepOneOut += "(" + curr + ")";
          curr = "";
        }
        stepOneOut += "))";
        exitDepths.erase(f);
        inMod = false;
      }
    }
  }
  if (curr != "") {
    stepOneOut += "(" + curr + ")";
    curr = "";
  }

  // bad hack to fix issue with parentheses not adding up
  int numEnd = 0;
  int numBegin = 0;
  for (auto c : stepOneOut) {
    if (c == ')')
      numEnd++;
    if (c == '(')
      numBegin++;
  }

  if (numBegin > numEnd) {
    for (int i = 0; i < numBegin - numEnd; i++) {
      stepOneOut += ")";
    }
  }

  // remove spaces
  std::string stepTwoOut = "";
  for (auto c : stepOneOut) {
    if (c != ' ') {
      stepTwoOut += c;
    }
  }

  // add implied multiplication and subtraction
  // implied multiplication is when 3x = (3)*(x)
  // implied subtraction is when -2 = (0) - (2)
  std::string stepThreeOut = "";
  for (auto it = stepTwoOut.begin(); it < stepTwoOut.end(); it++) {
    if (*it == '-') {
      if (it == stepTwoOut.begin()) {
        stepThreeOut += "(0)-";
      } else if (isOperator(*(it - 1))) {
        stepThreeOut += "(0)-";
      } else {
        stepThreeOut += "-";
      }
    } else if (*it == '(') {
      if (it != stepTwoOut.begin() && *(it - 1) == ')') {
        stepThreeOut += "*(";
      } else {
        stepThreeOut += "(";
      }
    } else {
      stepThreeOut += *it;
    }
  }

  return stepThreeOut;
}

// evaluate at a single x-value
double Equation::evalAtX(double x, bool useDeg) {
  double ret = 0;
  ret = baseUnit->evalUnit(x, useDeg);
  return ret;
}

// evaluate over a range of x-values
std::map<double, double> Equation::exportRange(double xPos, double dist,
                                               double resolution, bool scaleRes,
                                               bool useDeg) {
  std::map<double, double> ret;

  if (resolution == 0.0f)
    resolution = 0.1f;

  // scale the resolution based upon the zoom of the camera
  if (scaleRes)
    resolution = resolution * pow(dist, 0.5f);

  double startX = xPos - dist;

  for (double i = 0; i <= dist * 2 + resolution; i += resolution) {
    ret[startX + i] = evalAtX(startX + i, useDeg);
  }

  return ret;
}
