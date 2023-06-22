#ifndef PANEL_H
#define PANEL_H

#include <cmath>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <yanl/linear_algebra.h>
#include <yanl/matrix.h>

using json = nlohmann::json;

namespace panel {
struct PanelInput {
  int num_panels;
  double mach_number;
  double ellipse_ratio;
};

void to_json(json &j, const PanelInput &p) {
  j = json{{"num_panels", p.num_panels},
           {"mach_number", p.mach_number},
           {"ellipse_ratio", p.ellipse_ratio}};
}

void from_json(const json &j, PanelInput &p) {
  j.at("num_panels").get_to(p.num_panels);
  j.at("mach_number").get_to(p.mach_number);
  j.at("ellipse_ratio").get_to(p.ellipse_ratio);
}

class Panel : public PanelInput {
private:
  int num_points = 0;
  std::vector<double> x, y, xc, yc, ds, si, ci, theta, qn, qt, u, v, p;
  Panel(const PanelInput &input) {
    num_panels = input.num_panels;
    num_points = num_panels + 1;
    mach_number = input.mach_number;
    ellipse_ratio = input.ellipse_ratio;
    x.resize(num_points);
    y.resize(num_points);
    xc.resize(num_panels);
    yc.resize(num_panels);
    ds.resize(num_panels);
    ci.resize(num_panels);
    si.resize(num_panels);
    qt.resize(num_panels);
    qn.resize(num_panels);
    theta.resize(num_panels);
    u.resize(num_panels);
    v.resize(num_panels);
    p.resize(num_panels);
  }

  void body() {
    const int n = num_panels;
    const double fmn = mach_number;
    const double ratio = ellipse_ratio;

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

  std::string matelm() {
    double vx = 1.0;
    double vy = 0.0;
    auto R = yanl::matrix<double>(num_panels, 1);
    auto FN = yanl::matrix<double>(num_panels, num_panels);
    auto FT = yanl::matrix<double>(num_panels, num_panels);

    for (int k = 0; k < num_panels; ++k) {
      R(k, 0) = vx * si[k] - vy * ci[k];

      for (int j = 0; j < num_panels; ++j) {
        if (k == j) {
          FN(k, j) = 2.0 * M_PI;
          FT(k, j) = 0.0;
        } else {
          double dyj = si[j] * ds[j];
          double dxj = ci[j] * ds[j];
          double sph = ds[j] / 2.0;

          double xd = xc[k] - xc[j];
          double yd = yc[k] - yc[j];
          double rkj = std::sqrt(xd * xd + yd * yd);

          double bkj = std::atan2(yd, xd);
          double alj = std::atan2(dyj, dxj);
          double gkj = alj - bkj;

          double zik = rkj * std::cos(gkj);
          double etk = -rkj * std::sin(gkj);

          double r1s = std::pow((zik + sph), 2.0) + std::pow(etk, 2.0);
          double r2s = std::pow((zik - sph), 2.0) + std::pow(etk, 2.0);
          double qt = std::log(r1s / r2s);

          double den = zik * zik + etk * etk - sph * sph;
          double gnm = etk * ds[j];
          double qn = 2.0 * std::atan2(gnm, den);

          double ukj = qt * ci[j] - qn * si[j];
          double vkj = qt * si[j] + qn * ci[j];

          FN(k, j) = -ukj * si[k] + vkj * ci[k];
          FT(k, j) = ukj * ci[k] + vkj * si[k];
        }
      }
    }
    auto sde = yanl::linear_algebra::solve(FN, R);
    auto qts = FT * sde;
    auto qns = FN * sde;

    std::stringstream ss;
    ss << std::setprecision(3);
    for (int i = 0; i < num_panels; ++i) {
      theta[i] = std::atan2(yc[i], xc[i]);
      qt[i] = qts(i, 0) + vy * si[i] + vx * ci[i];
      qn[i] = qns(i, 0) + vy * ci[i] - vx * si[i];
      u[i] = vx - qns(i, 0) * si[i] + qts(i, 0) * ci[i];
      v[i] = vy + qns(i, 0) * ci[i] + qts(i, 0) * si[i];
      p[i] = 1.0 - std::pow(u[i], 2.0) - std::pow(v[i], 2.0);

      ss << "XY,YC = " << xc[i] << "\t" << yc[i] << "\tQN,QT = 0.00"
         << "\t" << qt[i] << "\tU,V = " << u[i] << "\t" << v[i]
         << "\tP = " << p[i] << "\n";
    }
    return ss.str();
  }

public:
  static std::string run(const PanelInput &input) {
    Panel data = Panel(input);
    data.body();
    return data.matelm();
  };

  static std::string run(const std::string &input) {
    auto j = json::parse(input);
    auto p = j.get<panel::PanelInput>();
    Panel data = Panel(p);
    data.body();
    return data.matelm();
  };
};

} // namespace panel

#endif