#include <capd/dynsys/C2OdeSolver.h>

void wrapC2OdeSolver(pybind11::module& mod) {
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::dynsys;
    using IMap = map::Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using StepControlType = ILastTermsStepControl;
    using CurveType = diffAlgebra::C2Curve<diffAlgebra::BasicC2Curve<IMap::MatrixType>>;
    using IC2OdeSolver = C2OdeSolver<IMap>;
    using VectorType = IC2OdeSolver::VectorType;
    using MatrixType = IC2OdeSolver::MatrixType;
    using ScalarType = IC2OdeSolver::ScalarType;
    using HessianType = IC2OdeSolver::HessianType;
    using size_type = IC2OdeSolver::size_type;
    using C2TimeJetType = IC2OdeSolver::C2TimeJetType;

    py::class_<IC2OdeSolver, OdeSolver<IMap, StepControlType, HighOrderEnclosure, CurveType>,
        BasicC2OdeSolver<IMap, StepControlType, CurveType>>
        (mod, "IC2OdeSolver")
        .def(py::init<typename IC2OdeSolver::VectorFieldType&, size_type>(), py::arg("field"), py::arg("order"))
        .def("encloseC2Map", &IC2OdeSolver::encloseC2Map)
        .def("computeRemainder", py::overload_cast<ScalarType, const VectorType&, C2TimeJetType&, C2TimeJetType&>
            (&IC2OdeSolver::computeRemainder))
        .def("initRemainderCoefficients", py::overload_cast<ScalarType, const VectorType&, unsigned>
            (&IC2OdeSolver::initRemainderCoefficients))
        .def("computeRemainderCoefficients",
            py::overload_cast<const VectorType&, const MatrixType&, const HessianType&>
            (&IC2OdeSolver::computeRemainderCoefficients))
        .def("computeRemainderCoefficients",
            py::overload_cast<ScalarType, const VectorType&, const MatrixType&, const HessianType&>
            (&IC2OdeSolver::computeRemainderCoefficients))
        .def("getStep", &IC2OdeSolver::getStep)
        ;
    }