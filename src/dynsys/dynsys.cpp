#include <capd/dynsys/StepControl.h>

#include "StepControlInterface.cpp"

void wrapDynsys(pybind11::module& mod) {
    using namespace capd::dynsys;

    wrapStepControlInterface<ILastTermsStepControl>(mod, "StepControlInterfaceILT");
    wrapStepControlInterface<IEncFoundStepControl>(mod, "StepControlInterfaceIEF");
}