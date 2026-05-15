#include <capd/dynsys/BasicC2OdeSolver.hpp>

void wrapBasicC2OdeSolver(pybind11::module& mod) {
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::dynsys;
    using IMap = map::Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using StepControlType = ILastTermsStepControl;
    using CurveType = diffAlgebra::C2Curve<diffAlgebra::BasicC2Curve<IMap::MatrixType>>;
    using IBasicC2OdeSolver = BasicC2OdeSolver<IMap, StepControlType, CurveType>;
    using VectorType = IBasicC2OdeSolver::VectorType;
    using MatrixType = IBasicC2OdeSolver::MatrixType;
    using ScalarType = IBasicC2OdeSolver::ScalarType;
    using HessianType = IBasicC2OdeSolver::HessianType;
    using size_type = IBasicC2OdeSolver::size_type;
    using IC0TimeJet = diffAlgebra::C0TimeJet<MatrixType::RowVectorType>;
    using IC1TimeJet = diffAlgebra::C1TimeJet<MatrixType>;
    using IC2TimeJet = diffAlgebra::C2TimeJet<MatrixType>;
    using ICnTimeJet = diffAlgebra::CnTimeJet<MatrixType, 0>;

    py::class_<IBasicC2OdeSolver, BasicOdeSolver<IMap, StepControlType, CurveType>>
        (mod, "IBasicC2OdeSolver")
        .def(py::init<typename IBasicC2OdeSolver::VectorFieldType&, size_type, const StepControlType&>(),
            py::arg("field"), py::arg("order"), py::arg("stepControl") = StepControlType())
        .def("__call__", static_cast<VectorType (IBasicC2OdeSolver::*)
            (VectorType, MatrixType&, HessianType&)>(&IBasicC2OdeSolver::operator()),
            "Computes next point on the trajectory, "
            "first and second order derivatives with respect to initial conditions. "
            "Initial conditions for variational equations are Id and zero, respectively.")
        .def("__call__", static_cast<VectorType (IBasicC2OdeSolver::*)
            (ScalarType&, const VectorType&, MatrixType&, HessianType&)>(&IBasicC2OdeSolver::operator()),
            "Computes next point on the trajectory of a nonautonomous system, "
            "first and second order derivatives with respect to initial conditions. "
            "Initial conditions for variational equations are Id and zero, respectively.")
        .def("__call__", static_cast<VectorType (IBasicC2OdeSolver::*)
            (VectorType, const MatrixType&, const HessianType&, MatrixType&, HessianType&)>
            (&IBasicC2OdeSolver::operator()),
            "The routine computes next point, derivatives and second order derivatives of a flow. "
            "Initial conditions for variational equations are V and H, respectively.")
        .def("__call__", static_cast<VectorType (IBasicC2OdeSolver::*)
            (ScalarType&, const VectorType&, const MatrixType&, const HessianType&, MatrixType&, HessianType&)>
            (&IBasicC2OdeSolver::operator()),
            "The routine computes next point, derivatives and second order derivatives of a nonautonomous flow. "
            "Initial conditions for variational equations are V and H, respectively.")
        .def("__call__", static_cast<void (IBasicC2OdeSolver::*) (IC0TimeJet&)>
            (&IBasicC2OdeSolver::operator()),
            "This operator computes image of the set (in given representation)")
        .def("__call__", static_cast<void (IBasicC2OdeSolver::*) (IC1TimeJet&)>
            (&IBasicC2OdeSolver::operator()),
            "This operator computes image of the set (in given representation)")
        .def("__call__", static_cast<void (IBasicC2OdeSolver::*) (IC2TimeJet&)>
            (&IBasicC2OdeSolver::operator()),
            "This operator computes image of the set (in given representation)")
        .def("__call__", static_cast<void (IBasicC2OdeSolver::*) (ICnTimeJet&)>
            (&IBasicC2OdeSolver::operator()),
            "This throws an exception, this solver cannot be used with this jet")
        ;
}