#pragma once

#include <cmath>
#include <iostream>

#include <yanl/matrix.h>

class ConstantElement {

private:
  double x1_, y1_;
  double x2_, y2_;
  double xbar_, ybar_;
  double dx_, dy_, ds_;
  double ci_, si_;

public:
  ConstantElement(double x1, double y1, double x2, double y2)
      : x1_(x1), y1_(y1), x2_(x2), y2_(y2) {
    dx_ = x2_ - x1_;
    dy_ = y2_ - y1_;
    ds_ = std::sqrt(dx_ * dx_ + dy_ * dy_);
    ci_ = dx_ / ds_;
    si_ = dy_ / ds_;
  }

  double get_x1() { return x1_; }
  double get_x2() { return x2_; }
  void print() {
    std::cout << "coords = (" << get_x1() << ", " << get_x2() << ")\n\n";
  }
};

std::vector<ConstantElement> model_elements () {
  std::vector<ConstantElement> v{};
  return v;
}

struct PanelResults {};

PanelResults solve(std::vector<ConstantElement>) {
  PanelResults results{};
  return results;
}
