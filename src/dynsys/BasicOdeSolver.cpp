#include <capd/dynsys/BasicOdeSolver.h>

template<typename StepControlType, typename CurveType>
void wrapBasicOdeSolver(pybind11::module& mod, const std::string& name) {
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::dynsys;
    using IMap = map::Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using BasicOdeSolverType = BasicOdeSolver<IMap, StepControlType, CurveType>;
    using VectorType = BasicOdeSolverType::VectorType;
    using MatrixType = BasicOdeSolverType::MatrixType;
    using ScalarType = BasicOdeSolverType::ScalarType;
    using size_type = BasicOdeSolverType::size_type;

    py::class_<BasicOdeSolverType, StepControlInterface<StepControlType, IMap::ScalarType>, CurveType>
        (mod, name.c_str())
        .def(py::init<typename BasicOdeSolverType::VectorFieldType&, size_type, const StepControlType&>(),
            py::arg("field"), py::arg("order"), py::arg("stepControl") = StepControlType())
        .def("__call__", static_cast<VectorType (BasicOdeSolverType::*) (VectorType)>(&BasicOdeSolverType::operator()),
            "Computes image of vector v after one time step.")
        .def("__call__", static_cast<VectorType (BasicOdeSolverType::*) (ScalarType&, const VectorType&)>
            (&BasicOdeSolverType::operator()),
            "Computes image of vector v after one time step. The argument t is updated in this procedure.")
        .def("__call__", static_cast<VectorType (BasicOdeSolverType::*) (VectorType, MatrixType&)>
            (&BasicOdeSolverType::operator()),
            "Computes image of vector v and derivatives of the flow with respect to init condition (v,identity). "
            "Version for autonomous systems.")
        .def("__call__", static_cast<VectorType (BasicOdeSolverType::*) (ScalarType&, const VectorType&, MatrixType&)>
            (&BasicOdeSolverType::operator()),
            "Computes image of vector v and derivatives of the flow with respect to init condition (v,identity). "
            "Version for nonautonomous systems. The argument t is updated in this procedure.")
        .def("__call__", static_cast<VectorType (BasicOdeSolverType::*) (VectorType, const MatrixType&, MatrixType&)>
            (&BasicOdeSolverType::operator()),
            "Computes image of vector v and derivatives of a flow with respect to init condition (v, derivative)")
        .def("__call__", static_cast<VectorType (BasicOdeSolverType::*)
            (ScalarType&, const VectorType&, const MatrixType&, MatrixType&)>
            (&BasicOdeSolverType::operator()),
            "Computes image of vector v and derivatives of a flow with respect to init condition (v, derivative). "
            "The argument t is updated in this procedure.")
        .def("getVectorField", py::overload_cast<>(&BasicOdeSolverType::getVectorField, py::const_),
            "Returns vector field")
        .def("setOrder", &BasicOdeSolverType::setOrder, "Sets the order of the Taylor method")
        .def("getStep", &BasicOdeSolverType::getStep, "Returns the time step made in the last call to this solver")
        .def("setStep", &BasicOdeSolverType::setStep, "Sets fixed time step and turns off step control")
        .def("computeCoefficientsAtCenter", py::overload_cast<const VectorType&, size_type>
            (&BasicOdeSolverType::computeCoefficientsAtCenter))
        .def("computeCoefficientsAtCenter", py::overload_cast<ScalarType, const VectorType&, size_type>
            (&BasicOdeSolverType::computeCoefficientsAtCenter))
        .def("computeCoefficients", py::overload_cast<const VectorType&, size_type>
            (&BasicOdeSolverType::computeCoefficients))
        .def("computeCoefficients", py::overload_cast<ScalarType, const VectorType&, size_type>
            (&BasicOdeSolverType::computeCoefficients))
        .def("computeCoefficients", py::overload_cast<const VectorType&, const MatrixType&, size_type>
            (&BasicOdeSolverType::computeCoefficients))
        .def("computeCoefficients", py::overload_cast<ScalarType, const VectorType&, const MatrixType&, size_type>
            (&BasicOdeSolverType::computeCoefficients))
        .def("getCurve", &BasicOdeSolverType::getCurve)
        .def("getCoeffNorm", &BasicOdeSolverType::getCoeffNorm)
        .def("dimension", &BasicOdeSolverType::dimension)
        .def("adjustTimeStep", &BasicOdeSolverType::adjustTimeStep,
            "sets time step but does not change step control settings (compare setStep)")
        .def("setMask", [](BasicOdeSolverType& solver, const std::vector<Multiindex>& multiindices) {
            solver.setMask(multiindices.begin(), multiindices.end());
        }, "The list should contain a range of Multiinideces the user requires to compute. "
            "The method automatically adds all the depending partial derivatives to this collection and defines "
            "a mask for computation of partial derivtives. The method causes undefined behavior if a multiindex "
            "in the collection exceeds limits of the vector field (like dimension, maximal allowed degree).")
        .def("addMultiindexToMask", &BasicOdeSolverType::addMultiindexToMask,
            "Adds new multiindex (along with dependencies) to the \b existing mask. "
            "causes undefined behavior if the mask has not been set before call to this method.")
        .def("resetMask", &BasicOdeSolverType::resetMask,
            "Resets the mask of derivatives. In consequence, full jet of derivatives will be computed after call "
            "to any method that computes derivative, hessian or jet.")
        ;
}