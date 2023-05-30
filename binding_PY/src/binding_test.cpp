#include "binding_test.h"


class PyVirtualClassImpl : public VirtualClass {
public:
    using VirtualClass::VirtualClass;

    void Do(int a) override {
        PYBIND11_OVERRIDE(void, VirtualClass, Do, a);
    }

};


void binding_test(pybind11::module_ &m) {

    pybind11::class_<VirtualClass, PyVirtualClassImpl>(m, "PyVirtualClassImpl")
            .def(pybind11::init<>())
            .def("Do1", &PyVirtualClassImpl::Do1);
}
