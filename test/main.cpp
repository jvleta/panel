#include <iostream>

#include <panel/panel.h>

int main() {
  auto p = ConstantElement(0.0, 0.0, 1.0, 1.0);
  p.print();
}