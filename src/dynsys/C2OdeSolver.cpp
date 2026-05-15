#include <capd/dynsys/C2OdeSolver.hpp>

template<typename C2OdeSolverType, typename... Sets>
void wrapOperatorsForC0C1C2(pybind11::class_<C2OdeSolverType,
    typename C2OdeSolverType::BaseTaylor, typename C2OdeSolverType::BaseC2Taylor>& solver)
{
    (..., solver.def("__call__", static_cast<void (C2OdeSolverType::*) (Sets&, Sets&)> (&C2OdeSolverType::operator()),
            "Computes image of the set (in set's representation) and stores it in the result set.")
        .def("__call__", static_cast<void (C2OdeSolverType::*) (Sets&)> (&C2OdeSolverType::operator()),
            "This operator computes image of the set (in given representation)"));
}

template<typename C2OdeSolverType, typename... Sets>
void wrapOperatorsForCn(pybind11::class_<C2OdeSolverType,
    typename C2OdeSolverType::BaseTaylor, typename C2OdeSolverType::BaseC2Taylor>& solver)
{
    (..., solver.def("__call__", static_cast<void (C2OdeSolverType::*) (Sets&, Sets&)> (&C2OdeSolverType::operator()),
            "This throws an exception, this solver cannot be used with this set.")
        .def("__call__", static_cast<void (C2OdeSolverType::*) (Sets&)> (&C2OdeSolverType::operator()),
            "This throws an exception, this solver cannot be used with this set"));
}

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
        BasicC2OdeSolver<IMap, StepControlType, CurveType>> solver(mod, "IC2OdeSolver");
    solver.def(py::init<typename IC2OdeSolver::VectorFieldType&, size_type>(), py::arg("field"), py::arg("order"))
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

        wrapOperatorsForC0C1C2<IC2OdeSolver, C0Rect2Set, C0TripletonSet, C0HORect2Set, C0HOTripletonSet,
            C1Rect2Set, C1HORect2Set, C11Rect2Set, C2Rect2Set>(solver);
        wrapOperatorsForCn<IC2OdeSolver, CnRect2Set>(solver);
    }