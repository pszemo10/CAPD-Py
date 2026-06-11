#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/native_enum.h>
#include "intervals/intervals.cpp"
#include "vectalg/vectalgModule.cpp"
#include "matrixAlgorithms/matrixAlgorithms.cpp"
#include "map/mapModule.cpp"
#include "diffAlgebra/diffAlgebraModule.cpp"
#include "dynset/dynset.cpp"
#include "dynsys/dynsysModule.cpp"
#include "poincare/poincareModule.cpp"

namespace py = pybind11;

PYBIND11_MODULE(capdpy, m, py::mod_gil_not_used()){
    wrapIntervals(m);
    wrapVectalgModule(m);
    wrapMatrixAlgorithms(m);
    wrapMapModule(m);
    wrapDiffAlgebraModule(m);
    wrapDynset(m);
    wrapDynsysModule(m);
    wrapPoincareModule(m);
}