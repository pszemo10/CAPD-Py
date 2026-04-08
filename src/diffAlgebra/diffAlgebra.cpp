#include "Hessian.cpp"
#include "CnContainer.cpp"
#include "Jet.cpp"

void wrapDiffAlgebra(pybind11::module_& mod){
    wrapHessian(mod);
    wrapCnContainer(mod);
    wrapJet(mod);
}