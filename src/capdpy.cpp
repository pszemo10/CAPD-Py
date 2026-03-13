#include <pybind11/pybind11.h>
#include "intervals/intervals.cpp"

namespace py = pybind11;

PYBIND11_MODULE(capdpy, m, py::mod_gil_not_used()){
    wrapIntervals(m);
}