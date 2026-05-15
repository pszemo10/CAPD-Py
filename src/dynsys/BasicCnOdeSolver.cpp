#include <capd/dynsys/BasicCnOdeSolver.hpp>

void wrapBasicCnOdeSolver(pybind11::module& mod) {
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::dynsys;
    using IMap = map::Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using StepControlType = IEncFoundStepControl;
    using CurveType = diffAlgebra::CnCurve<diffAlgebra::BasicCnCurve<IMap::MatrixType>>;
    using IBasicCnOdeSolver = BasicCnOdeSolver<IMap, StepControlType, CurveType>;
    using VectorType = IBasicCnOdeSolver::VectorType;
    using MatrixType = IBasicCnOdeSolver::MatrixType;
    using ScalarType = IBasicCnOdeSolver::ScalarType;
    using HessianType = IBasicCnOdeSolver::HessianType;
    using size_type = IBasicCnOdeSolver::size_type;
    using IC0TimeJet = diffAlgebra::C0TimeJet<MatrixType::RowVectorType>;
    using IC1TimeJet = diffAlgebra::C1TimeJet<MatrixType>;
    using IC2TimeJet = diffAlgebra::C2TimeJet<MatrixType>;
    using ICnTimeJet = diffAlgebra::CnTimeJet<MatrixType, 0>;

    py::class_<IBasicCnOdeSolver, StepControlInterface<StepControlType, IMap::ScalarType>, CurveType>
        (mod, "IBasicCnOdeSolver")
        .def(py::init<typename IBasicCnOdeSolver::VectorFieldType&, size_type, const StepControlType&>(),
            py::arg("field"), py::arg("order"), py::arg("stepControl") = StepControlType())
        .def("__call__", static_cast<VectorType (IBasicCnOdeSolver::*) (VectorType)>(&IBasicCnOdeSolver::operator()),
            "Computes image of vector v after one time step.")
        .def("__call__", static_cast<VectorType (IBasicCnOdeSolver::*) (ScalarType&, const VectorType&)>
            (&IBasicCnOdeSolver::operator()),
            "Computes image of vector v after one time step. The argument t is updated in this procedure.")
        .def("__call__", static_cast<VectorType (IBasicCnOdeSolver::*) (VectorType, MatrixType&)>
            (&IBasicCnOdeSolver::operator()),
            "Computes image of vector v and derivatives of the flow with respect to init condition (v,identity). "
            "Version for autonomous systems.")
        .def("__call__", static_cast<VectorType (IBasicCnOdeSolver::*) (ScalarType&, const VectorType&, MatrixType&)>
            (&IBasicCnOdeSolver::operator()),
            "Computes image of vector v and derivatives of the flow with respect to init condition (v,identity). "
            "Version for nonautonomous systems. The argument t is updated in this procedure.")
        .def("__call__", static_cast<VectorType (IBasicCnOdeSolver::*) (VectorType, const MatrixType&, MatrixType&)>
            (&IBasicCnOdeSolver::operator()),
            "Computes image of vector v and derivatives of a flow with respect to init condition (v, derivative)")
        .def("__call__", static_cast<VectorType (IBasicCnOdeSolver::*)
            (ScalarType&, const VectorType&, const MatrixType&, MatrixType&)>
            (&IBasicCnOdeSolver::operator()),
            "Computes image of vector v and derivatives of a flow with respect to init condition (v, derivative). "
            "The argument t is updated in this procedure.")
        .def("__call__", static_cast<void (IBasicCnOdeSolver::*) (IC0TimeJet&)>
            (&IBasicCnOdeSolver::operator()),
            "This operator computes image of the set (in given representation)")
        .def("__call__", static_cast<void (IBasicCnOdeSolver::*) (IC1TimeJet&)>
            (&IBasicCnOdeSolver::operator()),
            "This operator computes image of the set (in given representation)")
        .def("__call__", static_cast<void (IBasicCnOdeSolver::*) (IC2TimeJet&)>
            (&IBasicCnOdeSolver::operator()),
            "This operator computes image of the set (in given representation)")
        .def("__call__", static_cast<void (IBasicCnOdeSolver::*) (ICnTimeJet&)>
            (&IBasicCnOdeSolver::operator()),
            "This operator computes image of the set (in given representation)")
        .def("__call__", static_cast<VectorType (IBasicCnOdeSolver::*)
            (VectorType, MatrixType&, HessianType&)>(&IBasicCnOdeSolver::operator()),
            "Computes next point on the trajectory, "
            "first and second order derivatives with respect to initial conditions. "
            "Initial conditions for variational equations are Id and zero, respectively.")
        .def("__call__", static_cast<VectorType (IBasicCnOdeSolver::*)
            (ScalarType&, const VectorType&, MatrixType&, HessianType&)>(&IBasicCnOdeSolver::operator()),
            "Computes next point on the trajectory of a nonautonomous system, "
            "first and second order derivatives with respect to initial conditions. "
            "Initial conditions for variational equations are Id and zero, respectively.")
        .def("__call__", static_cast<VectorType (IBasicCnOdeSolver::*)
            (VectorType, const MatrixType&, const HessianType&, MatrixType&, HessianType&)>
            (&IBasicCnOdeSolver::operator()),
            "The routine computes next point, derivatives and second order derivatives of a flow. "
            "Initial conditions for variational equations are V and H, respectively.")
        .def("__call__", static_cast<VectorType (IBasicCnOdeSolver::*)
            (ScalarType&, const VectorType&, const MatrixType&, const HessianType&, MatrixType&, HessianType&)>
            (&IBasicCnOdeSolver::operator()),
            "The routine computes next point, derivatives and second order derivatives of a nonautonomous flow. "
            "Initial conditions for variational equations are V and H, respectively.")
        .def("__call__", static_cast<VectorType (IBasicCnOdeSolver::*) (ScalarType&, IBasicCnOdeSolver::JetType&)>
            (&IBasicCnOdeSolver::operator()),
            "Initial conditions for the trajectory and for variational equations "
            "up to given degree are given in argument in_out_coeffs. "
            "The full result is stored in in_out_coeffs and also the new point on the trajectory is returned. "
            "Note: CnCoeffType is a data structure that stores current time.")
        .def("computeCoefficientsAtCenter", py::overload_cast<const VectorType&, size_type>
            (&IBasicCnOdeSolver::computeCoefficientsAtCenter))
        .def("computeCoefficientsAtCenter", py::overload_cast<ScalarType, const VectorType&, size_type>
            (&IBasicCnOdeSolver::computeCoefficientsAtCenter))
        .def("computeCoefficients", py::overload_cast<const VectorType&, size_type>
            (&IBasicCnOdeSolver::computeCoefficients))
        .def("computeCoefficients", py::overload_cast<ScalarType, const VectorType&, size_type>
            (&IBasicCnOdeSolver::computeCoefficients))
        .def("computeCoefficients", py::overload_cast<const VectorType&, const MatrixType&, size_type>
            (&IBasicCnOdeSolver::computeCoefficients))
        .def("computeCoefficients", py::overload_cast<ScalarType, const VectorType&, const MatrixType&, size_type>
            (&IBasicCnOdeSolver::computeCoefficients))
        .def("getVectorField", py::overload_cast<>(&IBasicCnOdeSolver::getVectorField, py::const_),
            "Returns vector field")
        .def("setOrder", &IBasicCnOdeSolver::setOrder, "Sets the order of the Taylor method")
        .def("getStep", &IBasicCnOdeSolver::getStep, "Returns current time step")
        .def("setStep", &IBasicCnOdeSolver::setStep, "Sets fixed time step and turns off step control")
        .def("getCurve", &IBasicCnOdeSolver::getCurve)
        .def("degree", &IBasicCnOdeSolver::degree)
        .def("getCoeffNorm", &IBasicCnOdeSolver::getCoeffNorm)
        .def("adjustTimeStep", &IBasicCnOdeSolver::adjustTimeStep,
            "sets time step but does not change step control settings (compare setStep)")
        .def("setMask", [](IBasicCnOdeSolver& solver, const std::vector<Multiindex>& multiindices) {
            solver.setMask(multiindices.begin(), multiindices.end());
        }, "The list should contain a range of Multiinideces the user requires to compute. "
            "The method automatically adds all the depending partial derivatives to this collection and defines "
            "a mask for computation of partial derivtives. The method causes undefined behavior if a multiindex "
            "in the collection exceeds limits of the vector field (like dimension, maximal allowed degree).")
        .def("addMultiindexToMask", &IBasicCnOdeSolver::addMultiindexToMask,
            "Adds new multiindex (along with dependencies) to the \b existing mask. "
            "causes undefined behavior if the mask has not been set before call to this method.")
        .def("resetMask", &IBasicCnOdeSolver::resetMask,
            "Resets the mask of derivatives. In consequence, full jet of derivatives will be computed after call "
            "to any method that computes derivative, hessian or jet.")
        ;
}