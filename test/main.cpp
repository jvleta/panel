#include <iostream>

#include <panel/panel.h>

int main() {
  PanelInput p{20, 21, 0.0, 0.5};
  const auto r = Panel::run(p);
}
