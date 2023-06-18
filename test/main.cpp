#include <iostream>

#include <panel/panel.h>

int main() {
  PanelInput p{20, 21, 0.0, 0.5};
  const auto r = panel(p);

  // output element parameters
  std::cout << "i,x,y,xc,yc\n";
  for (int i = 0; i < r.num_panels; ++i) {
    std::cout << i + 1 << " " << r.xc[i] << " " << r.yc[i] << "\n";
  }
}
