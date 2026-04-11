#include <capd/dynsys/StepControl.h>

template<typename StepControlPolicy>
void wrapStepControlInterface(pybind11::module& mod, const std::string name) {
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::dynsys;
    using IMap = map::Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using StepControlInterfaceType = StepControlInterface<StepControlPolicy, IMap::ScalarType>;

    py::class_<StepControlInterfaceType>(mod, name.c_str())
        .def(py::init<>())
        .def("turnOnStepControl", &StepControlInterfaceType::turnOnStepControl)
        .def("turnOffStepControl", &StepControlInterfaceType::turnOffStepControl)
        .def("onOffStepControl", &StepControlInterfaceType::onOffStepControl)
        .def("getStepControl", &StepControlInterfaceType::getStepControl)
        .def("setStepControl", &StepControlInterfaceType::setStepControl)
        .def("isStepChangeAllowed", &StepControlInterfaceType::isStepChangeAllowed)
        .def("setAbsoluteTolerance", &StepControlInterfaceType::setAbsoluteTolerance)
        .def("setRelativeTolerance", &StepControlInterfaceType::setRelativeTolerance)
        .def("getAbsoluteTolerance", &StepControlInterfaceType::getAbsoluteTolerance)
        .def("getRelativeTolerance", &StepControlInterfaceType::getRelativeTolerance)
        .def("getMaxStep", &StepControlInterfaceType::getMaxStep)
        .def("setMaxStep", &StepControlInterfaceType::setMaxStep)
        ;
}