#ifndef PANEL_H
#define PANEL_H

#include <cmath>
#include <iostream>

#include <yanl/matrix.h>

struct PanelInput {
  int num_panels;
  int num_points;
  double mach_number;
  double ratio;
};

struct PanelData : PanelInput {
  std::vector<double> x, y, xc, yc, ds, si, ci;
  PanelData(const PanelInput &input) {
    num_panels = input.num_panels;
    num_points = input.num_panels + 1;
    mach_number = input.mach_number;
    ratio = input.ratio;
    x.resize(num_points);
    y.resize(num_points);
    xc.resize(num_panels);
    yc.resize(num_panels);
    ds.resize(num_panels);
    ci.resize(num_panels);
    si.resize(num_panels);
  }
};

void body(PanelData *data) {

  auto &x = data->x;
  auto &y = data->y;
  auto &xc = data->xc;
  auto &yc = data->yc;
  auto &ds = data->ds;
  auto &ci = data->ci;
  auto &si = data->si;
  const int n = data->num_panels;
  const double fmn = data->mach_number;
  const double ratio = data->ratio;

  // body points
  const double fac = std::sqrt(1.0 - std::pow(fmn, 2.0));
  const int nhlff = n / 2 + 1;
  const int nhh = nhlff + 1;
  const int an = nhlff - 1;
  const double pi = M_PI;
  const double dth = pi / an;

  for (int i = 0; i < n / 2 + 1; ++i) {
    double th = pi - i * dth;
    x[i] = std::cos(th);
    y[i] = ratio * std::sin(th);
    // prandtl-glauert transformation
    y[i] *= fac;
  }

  // reflect for coordinates of lower half
  for (int i = n / 2 + 1; i < n; ++i) {
    x[i] = x[n - i];
    y[i] = -y[n - i];
  }

  x[n] = x[0];
  y[n] = y[0];

  // place control points at the center of panels
  for (int i = 0; i < n; ++i) {
    xc[i] = 0.5 * (x[i] + x[i + 1]);
    yc[i] = 0.5 * (y[i] + y[i + 1]);
  }

  // // calculate panel spans, cos and sin of angles
  for (int i = 0; i < n; ++i) {
    double sx = x[i + 1] - x[i];
    double sy = y[i + 1] - y[i];
    ds[i] = std::sqrt(std::pow(sx, 2.0) + std::pow(sy, 2.0));
    ci[i] = sx / ds[i];
    si[i] = sy / ds[i];
  }
}

PanelData panel(const PanelInput &input) {
  PanelData data = PanelData(input);
  body(&data);
  return data;
};

// class ConstantElement {

// private:
//   double x1_, y1_;
//   double x2_, y2_;
//   double xbar_, ybar_;
//   double dx_, dy_, ds_;
//   double ci_, si_;

// public:
//   ConstantElement(double x1, double y1, double x2, double y2)
//       : x1_(x1), y1_(y1), x2_(x2), y2_(y2) {
//     dx_ = x2_ - x1_;
//     dy_ = y2_ - y1_;
//     ds_ = std::sqrt(dx_ * dx_ + dy_ * dy_);
//     ci_ = dx_ / ds_;
//     si_ = dy_ / ds_;
//   }

//   double get_x1() { return x1_; }
//   double get_x2() { return x2_; }
//   void print() {
//     std::cout << "coords = (" << get_x1() << ", " << get_x2() << ")\n\n";
//   }
// };

// std::vector<ConstantElement> model_elements () {
//   std::vector<ConstantElement> v{};
//   return v;
// }

// struct PanelResults {};

// PanelResults solve(std::vector<ConstantElement>) {
//   PanelResults results{};
//   return results;
// }

#endif