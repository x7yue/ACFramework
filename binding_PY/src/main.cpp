#include <pybind11/pybind11.h>
#include "binding_test.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

int add(int i, int j) {
    return i + j;
}

namespace py = pybind11;

/**
 * 绑定一个 hello world
 * */
void bind_hello(pybind11::module_ &m) {
    m.def("add", &add, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");

    m.def("subtract", [](int i, int j) {
        return i - j;
    }, R"pbdoc(
        Subtract two numbers
        Some other explanation about the subtract function.
    )pbdoc");
}


PYBIND11_MODULE(acf_py, m
) {
    m.doc() = R"pbdoc(
        Acf python binding
    )pbdoc";
    // hello world
    bind_hello(m);

    binding_test(m);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}