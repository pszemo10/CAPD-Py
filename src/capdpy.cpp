#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/native_enum.h>
#include "intervals/intervals.cpp"
#include "vectalg/vectalg.cpp"
#include "matrixAlgorithms/matrixAlgorithms.cpp"
#include "map/map.cpp"
#include "diffAlgebra/diffAlgebra.cpp"
#include "dynset/dynset.cpp"
#include "dynsys/dynsys.cpp"
#include "poincare/poincare.cpp"

namespace py = pybind11;

PYBIND11_MODULE(capdpy, m, py::mod_gil_not_used()){
    wrapIntervals(m);
    wrapVectalg(m);
    wrapMatrixAlgorithms(m);
    wrapMapModule(m);
    wrapDiffAlgebra(m);
    wrapDynset(m);
    wrapDynsys(m);
    wrapPoincare(m);
}