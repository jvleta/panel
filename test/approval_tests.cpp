#include <filesystem>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

#include "gtest/gtest.h"
#include "ApprovalTests/Approvals.h"

#include <panel/panel.h>


TEST(panel_tests, INPR1) {
  auto j = json::parse(R"({"num_panels": 20, "mach_number": 0.0, "ellipse_ratio": 0.5})");
  auto p = j.get<panel::PanelInput>();
  const auto r = panel::Panel::run(p);
  ApprovalTests::Approvals::verify(r);
}