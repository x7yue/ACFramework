//
// Created by Administrator on 2023/5/30.
//
#include <pybind11/pybind11.h>
#include <iostream>

#ifndef ACF_PY_BINDING_TEST_H
#define ACF_PY_BINDING_TEST_H


void binding_test(pybind11::module_ &m);

class VirtualClass {
public:
    virtual void Do(int a) {
        std::cout << "VirtualClass: " << a << std::endl;
    }

    void Do1(int a){
        Do(a);
    }
};


#endif //ACF_PY_BINDING_TEST_H
