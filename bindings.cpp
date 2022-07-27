#include <emscripten/bind.h>

using namespace emscripten;

#include "panel.h"

EMSCRIPTEN_BINDINGS(panel) {
    class_<ConstantElement>("ConstantElement")
    .constructor<double, double, double, double>()
    .function("print", &ConstantElement::print);
}