#include <capd/dynsys/OdeSolver.h>

template<typename CurveType>
void wrapOdeSolver(pybind11::module& mod, const std::string& name) {
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::dynsys;
    using IMap = map::Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using StepControlType = ILastTermsStepControl;
    using OdeSolverType = OdeSolver<IMap, StepControlType, HighOrderEnclosure, CurveType>;
    using VectorType = OdeSolverType::VectorType;
    using MatrixType = OdeSolverType::MatrixType;
    using ScalarType = OdeSolverType::ScalarType;
    using size_type = OdeSolverType::size_type;
    using C1TimeJetType = OdeSolverType::C1TimeJetType;

    py::class_<OdeSolverType, BasicOdeSolver<IMap, StepControlType, CurveType>>
        (mod, name.c_str(), py::multiple_inheritance())
        .def(py::init<typename OdeSolverType::VectorFieldType&, size_type, const StepControlType&>(),
            py::arg("field"), py::arg("order"), py::arg("stepControl") = StepControlType())
        .def("setOrder", &OdeSolverType::setOrder, "Sets the order of the Taylor method.")
        .def("Phi", &OdeSolverType::Phi)
        .def("JacPhi", &OdeSolverType::JacPhi)
        .def("enclosure", &OdeSolverType::enclosure)
        .def("Remainder", &OdeSolverType::Remainder)
        .def("encloseC0Map", &OdeSolverType::encloseC0Map)
        .def("encloseC1Map", &OdeSolverType::encloseC1Map)
        .def("computeRemainderCoefficients", py::overload_cast<const VectorType&>
            (&OdeSolverType::computeRemainderCoefficients))
        .def("computeRemainderCoefficients", py::overload_cast<const VectorType&, const MatrixType&>
            (&OdeSolverType::computeRemainderCoefficients))
        .def("computeRemainderCoefficients", py::overload_cast<ScalarType, const VectorType&>
            (&OdeSolverType::computeRemainderCoefficients))
        .def("computeRemainderCoefficients", py::overload_cast<ScalarType,const VectorType&, const MatrixType&>
            (&OdeSolverType::computeRemainderCoefficients))
        .def("initRemainderCoefficients", &OdeSolverType::initRemainderCoefficients)
        .def("computeRemainder", py::overload_cast<ScalarType, const VectorType&, VectorType&, VectorType&>
            (&OdeSolverType::computeRemainder))
        .def("computeRemainder", py::overload_cast<ScalarType, const VectorType&, C1TimeJetType&, C1TimeJetType&>
            (&OdeSolverType::computeRemainder))
        .def("computeTaylorCoefficients", &OdeSolverType::computeTaylorCoefficients)
        .def("computeImplicitCoefficients", &OdeSolverType::computeImplicitCoefficients)
        .def("getCoeffNorm", &OdeSolverType::getCoeffNorm)
        .def("getStep", &OdeSolverType::getStep)
        .def("getImplicitCurve", &OdeSolverType::getImplicitCurve)
        .def("computeTimeStep", &OdeSolverType::computeTimeStep)
        ;
}