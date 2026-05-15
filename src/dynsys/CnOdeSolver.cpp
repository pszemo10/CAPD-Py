#include <capd/dynsys/CnOdeSolver.hpp>


template<typename CnOdeSolverType, typename... Sets>
void wrapOperatorsForSets(pybind11::class_<CnOdeSolverType, typename CnOdeSolverType::BaseTaylor>& solver)
{
    (..., solver.def("__call__", static_cast<void (CnOdeSolverType::*) (Sets&)> (&CnOdeSolverType::operator()),
            "This operator computes image of the set (in given representation)")
        .def("__call__", static_cast<void (CnOdeSolverType::*) (Sets&, Sets&)> (&CnOdeSolverType::operator()),
            "Computes image of the set (in set's representation) and stores it in the result set."));
}

void wrapCnOdeSolver(pybind11::module& mod) {
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::dynsys;
    using IMap = map::Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using StepControlType = IEncFoundStepControl;
    using CurveType = diffAlgebra::CnCurve<diffAlgebra::BasicCnCurve<IMap::MatrixType>>;
    using ICnOdeSolver = CnOdeSolver<IMap, StepControlType, FirstOrderEnclosure, CurveType>;
    using VectorType = ICnOdeSolver::VectorType;
    using MatrixType = ICnOdeSolver::MatrixType;
    using ScalarType = ICnOdeSolver::ScalarType;
    using HessianType = ICnOdeSolver::HessianType;
    using size_type = ICnOdeSolver::size_type;
    using JetType = ICnOdeSolver::JetType;
    using C1TimeJetType = ICnOdeSolver::C1TimeJetType;
    using C2TimeJetType = ICnOdeSolver::C2TimeJetType;

    py::class_<ICnOdeSolver, BasicCnOdeSolver<IMap, StepControlType, CurveType>>
        solver (mod, "ICnOdeSolver", py::multiple_inheritance());
    solver.def(py::init<typename ICnOdeSolver::VectorFieldType&, size_type, const StepControlType&>(),
            py::arg("field"), py::arg("order"), py::arg("stepControl") = StepControlType())
        .def("Phi", &ICnOdeSolver::Phi)
        .def("JacPhi", &ICnOdeSolver::JacPhi)
        .def("enclosure", &ICnOdeSolver::enclosure)
        .def("Remainder", &ICnOdeSolver::Remainder)
        .def("encloseC0Map", &ICnOdeSolver::encloseC0Map)
        .def("JacRemainder", &ICnOdeSolver::JacRemainder)
        .def("encloseC1Map", &ICnOdeSolver::encloseC1Map)
        .def("encloseC2Map", &ICnOdeSolver::encloseC2Map)
        .def("c2Remainder", &ICnOdeSolver::c2Remainder)
        .def("encloseCnMap", &ICnOdeSolver::encloseCnMap<JetType>)
        .def("cnEnclosure", &ICnOdeSolver::cnEnclosure<JetType>)
        .def("cnRemainder", &ICnOdeSolver::cnRemainder<JetType>)
        .def("getStep", &ICnOdeSolver::getStep)
        .def("getCoeffNorm", &ICnOdeSolver::getCoeffNorm)
        .def("computeRemainderCoefficients", py::overload_cast<const VectorType&>
            (&ICnOdeSolver::computeRemainderCoefficients))
        .def("computeRemainderCoefficients", py::overload_cast<const VectorType&, const MatrixType&>
            (&ICnOdeSolver::computeRemainderCoefficients))
        .def("computeRemainderCoefficients", py::overload_cast<ScalarType, const VectorType&>
            (&ICnOdeSolver::computeRemainderCoefficients))
        .def("computeRemainderCoefficients", py::overload_cast<ScalarType,const VectorType&, const MatrixType&>
            (&ICnOdeSolver::computeRemainderCoefficients))
        .def("computeRemainder", static_cast<void (ICnOdeSolver::*)
            (ScalarType, const VectorType&, VectorType&, VectorType&)>
            (&ICnOdeSolver::computeRemainder))
        .def("computeRemainder", static_cast<void (ICnOdeSolver::*)
            (ScalarType, const VectorType&, C1TimeJetType&, C1TimeJetType&)>
            (&ICnOdeSolver::computeRemainder))
        .def("computeRemainder", static_cast<void (ICnOdeSolver::*)
            (ScalarType, const VectorType&, C2TimeJetType&, C2TimeJetType&)>
            (&ICnOdeSolver::computeRemainder))
        .def("computeRemainder", &ICnOdeSolver::computeRemainder<JetType>)
        .def("sumTaylorSeries", static_cast<void (ICnOdeSolver::*)
            (VectorType&, MatrixType&)>(&ICnOdeSolver::sumTaylorSeries))
        .def("sumTaylorSeries", static_cast<void (ICnOdeSolver::*)
            (VectorType&, MatrixType&, HessianType&)>
            (&ICnOdeSolver::sumTaylorSeries))
        .def("sumTaylorSeries", &ICnOdeSolver::sumTaylorSeries<JetType>)
        .def("computeTimeStep", &ICnOdeSolver::computeTimeStep)
        ;

        wrapOperatorsForSets<ICnOdeSolver, C0Rect2Set, C0TripletonSet, 
            C1Rect2Set, C11Rect2Set, C2Rect2Set, CnRect2Set>(solver);
}