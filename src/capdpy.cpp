#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include "intervals/intervals.cpp"
#include "vectalg/vectalg.cpp"

namespace py = pybind11;

PYBIND11_MODULE(capdpy, m, py::mod_gil_not_used()){
    wrapIntervals(m);
    wrapVectalg(m);
}