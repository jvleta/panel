#include <filesystem>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

#include "gtest/gtest.h"
#include "ApprovalTests/Approvals.h"

#include <panel/panel.h>

TEST(panel_tests, INPR1) {
  PanelInput p{20, 21, 0.0, 0.5};
  const auto r = Panel::run(p);
  ApprovalTests::Approvals::verify(r);
}