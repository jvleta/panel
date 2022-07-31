#include <emscripten/bind.h>
#include <vector>

using namespace emscripten;

#include <panel/panel.h>

void dostuff(ConstantElement ce) {
 ce.print();
}

// std::vector<ConstantElement> elements; 


EMSCRIPTEN_BINDINGS(panel) {
    class_<ConstantElement>("ConstantElement")
    .constructor<double, double, double, double>()
    .function("print", &ConstantElement::print);

    function("dostuff", &dostuff);

    function("modelElements", &model_elements);

    register_vector<ConstantElement>("vector<ConstantElement>");

}