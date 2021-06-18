#include "unit.h"

#include <algorithm>
#include <iostream>
#include <regex>

bool Unit::isOperator(char c) {
  switch (c) {
  case '+':
  case '-':
  case '/':
  case '*':
  case '^':
    return true;
  default:
    return false;
  }
}

Unit::Unit(std::string eq) {
  eqStr = eq;
  modExp = false;

  // deal with empty unit
  if (eq == "()") {
    hasVar = false;
    noVarValDeg = 0;
    noVarValRad = 0;
    return;
  }

  // check if the expression has a function
  if (eq.size() >= 3) {
    if (eq.at(0) == 's' || eq.at(0) == 't' || eq.at(0) == 'c') {
      modExp = true;
    }
  }

  // process the expression if it has a function
  if (modExp) {
    mod t = mod::NONE;
    int subPos = 3;
    switch (eq.at(1)) {
    case 'q':
      t = mod::SQRT;
      subPos = 4;
      break;
    case 'i':
      t = mod::SIN;
      break;
    case 'o':
      t = mod::COS;
      break;
    case 'a':
      t = mod::TAN;
      break;
    }
    Modulator temp;
    temp.setM(t);
    modUnit =
        std::make_pair(temp, new Unit(eq.substr(subPos, eq.length() - subPos)));
  } else {
    // process the expression if it doesn't have a function
    int parenDepth = 0;
    std::string curr = "";
    for (auto c : eq) {
      if (c == '(') {
        parenDepth++;
      } else if (c == ')') {
        parenDepth--;
      }
      if (parenDepth == 0) {
        if (curr != "") {
          Unit temp(curr);
          exp.push_back(temp);
          curr = "";
        }
        if (isOperator(c)) {
          Operator o(c);
          exp.push_back(o);
        }
      } else {
        if (!(parenDepth == 1 && c == '(')) {
          curr += c;
        }
      }
    }
  }

  // detect if the expression has a variable
  // if it does have a variable, then we let it be
  // otherwise, we evaluate it so we don't have to re-evaluate it every time
  bool tempHV = false;
  for (auto c : eqStr) {
    if (c == 'x' || c == 'y') {
      tempHV = true;
      break;
    }
  }

  if (!tempHV) {
    hasVar = true;
    noVarValDeg = this->evalUnit(0, true);
    noVarValRad = this->evalUnit(0, false);
  }
  hasVar = tempHV;
}

Unit::~Unit() {}

double Unit::evalUnit(double x, bool useDeg) {
  // if the expression does not have a variable, then it will be the same
  // every time and we can just return that value
  if (!hasVar) {
    return useDeg ? noVarValDeg : noVarValRad;
  }
  // std::cout << eqStr << std::endl;

  // evaluate expression if it has a function
  if (modExp) {

    double val = modUnit.second->evalUnit(x, useDeg);
    if (useDeg) {
      const double pi = 3.14159f;
      val = val * pi;
      val = val / 180.0f;
    }

    return modUnit.first.applyMod(val);
  } else {
    // evaluate expression if it does not have a function
    // return if its just x
    if (eqStr == "x") {
      return x;
    }
    // return if its just a number
    std::smatch match;
    std::regex isNum("^(\\d*)(.?)(\\d*)$");
    if (std::regex_match(eqStr, match, isNum)) {
      return atof(match[0].str().c_str());
    }
    // otherwise evaluate expression
    std::vector<std::variant<double, Operator>> opVec;
    for (auto i : exp) {
      if (std::holds_alternative<Unit>(i)) {
        opVec.push_back(std::get<Unit>(i).evalUnit(x, useDeg));
      } else if (std::holds_alternative<Operator>(i)) {
        opVec.push_back(std::get<Operator>(i));
      } else if (std::holds_alternative<double>(i)) {
        opVec.push_back(std::get<double>(i));
      }
    }

    return evalOps(opVec);
  }
  return x;
}

double Unit::evalOps(std::vector<std::variant<double, Operator>> opVec) {
  // handle invalid expressions
  for (auto it = opVec.begin(); it < opVec.end(); it++) {
    if (std::holds_alternative<Operator>(*it)) {
      if (it == opVec.end() - 1) {
        return 0;
      }
      if (!std::holds_alternative<double>(*(it - 1))) {
        return 0;
      }
      if (!std::holds_alternative<double>(*(it + 1))) {
        return 0;
      }
    }
  }
  // order of operations: exponents, multiplication and division, addition and
  // subtraction
  //
  // exponents:
  for (auto it = opVec.begin(); it < opVec.end(); it++) {
    if (std::holds_alternative<Operator>(*it)) {
      Operator o = std::get<Operator>(*it);
      if (o.getOp() == '^') {
        double lhs, rhs;
        lhs = std::get<double>(*(it - 1));
        rhs = std::get<double>(*(it + 1));
        auto er = (it - 1);
        opVec.erase(er);
        opVec.erase(er);
        opVec.erase(er);
        opVec.insert(er, o.evalOp(lhs, rhs));
      }
    }
  }

  // multiplication and division:
  for (auto it = opVec.begin(); it < opVec.end(); it++) {
    if (std::holds_alternative<Operator>(*it)) {
      Operator o = std::get<Operator>(*it);
      if (o.getOp() == '*' || o.getOp() == '/') {
        double lhs, rhs;
        lhs = std::get<double>(*(it - 1));
        rhs = std::get<double>(*(it + 1));
        auto er = (it - 1);
        opVec.erase(er);
        opVec.erase(er);
        opVec.erase(er);
        opVec.insert(er, o.evalOp(lhs, rhs));
      }
    }
  }

  // addition and subtraction:
  for (auto it = opVec.begin(); it < opVec.end(); it++) {
    if (std::holds_alternative<Operator>(*it)) {
      Operator o = std::get<Operator>(*it);
      if (o.getOp() == '+' || o.getOp() == '-') {
        double lhs, rhs;
        lhs = std::get<double>(*(it - 1));
        rhs = std::get<double>(*(it + 1));
        auto er = (it - 1);
        opVec.erase(er);
        opVec.erase(er);
        opVec.erase(er);
        opVec.insert(er, o.evalOp(lhs, rhs));
      }
    }
  }
  if (opVec.size() == 1 && std::holds_alternative<double>(*opVec.begin())) {
    return std::get<double>(*opVec.begin());
  } else {
    if (opVec.size() == 1) {
      std::cout << "lonely operator!" << std::endl;
      return 0;
    }
    return evalOps(opVec);
  }
}
