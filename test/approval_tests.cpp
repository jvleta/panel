#include "gtest/gtest.h"
#include "ApprovalTests/Approvals.h"

#include "panel/panel.h"

TEST(panel_tests, INPR1) {
  auto input = R"({"num_panels": 20, "mach_number": 0.0, "ellipse_ratio": 0.5})";
  const auto r = panel::Panel::run(input);
  ApprovalTests::Approvals::verify(r);
}