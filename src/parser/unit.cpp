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
  if (eq.size() >= 3) {
    if (eq.at(0) == 's' || eq.at(0) == 't' || eq.at(0) == 'c') {
      modExp = true;
    }
  }
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
}

Unit::~Unit() {}

double Unit::evalUnit(double x) {
  // std::cout << eqStr << std::endl;
  if (modExp) {
    double val = modUnit.second->evalUnit(x);
    return modUnit.first.applyMod(val);
  } else {
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
        opVec.push_back(std::get<Unit>(i).evalUnit(x));
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
