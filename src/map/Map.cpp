#include <capd/map/Map.h>

void wrapMap(pybind11::module &mod) {
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::map;
    using IMap = Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using VectorType = typename IMap::VectorType;
    using MatrixType = typename IMap::MatrixType;
    using ScalarType = typename IMap::ScalarType;
    using JetType = typename IMap::JetType;
    using HessianType = typename IMap::HessianType;


    py::class_<IMap, BasicFunction<ScalarType>>(mod, "IMap")
        .def(py::init<>())
        .def(py::init<const std::string&, IMap::size_type>(),
        "parses expression from given string. Allocates memory for jet propagation of degree 'degree'",
        py::arg("f"), py::pos_only(),py::arg("degree")=1)
        .def("__call__", py::overload_cast<const VectorType&>(&IMap::operator(), py::const_),
            "evaluates map at a given vector.")
        .def("__call__", py::overload_cast<ScalarType, const VectorType&>(&IMap::operator(), py::const_),
            "evaluates map at a given vector and for given time.")
        .def("__call__", py::overload_cast<const VectorType&, MatrixType&>(&IMap::operator(), py::const_),
            "computes simultaneously value and derivative of the map for a given vector.")
        .def("__call__", py::overload_cast<ScalarType, const VectorType&, MatrixType&>
            (&IMap::operator(), py::const_),
            "computes simultaneously value and derivative of the map for a given vector and time.")
        .def("__getitem__", &IMap::operator[],
            "computes derivative of the map for a given vector.")
        .def("derivative", py::overload_cast<const VectorType&>(&IMap::derivative, py::const_),
            "computes derivative of the map for a given vector.")
        .def("derivative", py::overload_cast<ScalarType, const VectorType&>
            (&IMap::derivative, py::const_),
            "computes derivative of the map for a given vector and time.")
        .def("homogenousPolynomial", static_cast<void (IMap::*)
            (MatrixType&) const>
            (&IMap::homogenousPolynomial),
            "Computes derivative of the map at a vector 'u' "
            "that was send to any vector or function evaluating value. "
            "In this case computation can be speeded up.")
        .def("homogenousPolynomial", static_cast<void (IMap::*)
            (const MatrixType&, HessianType&) const>
            (&IMap::homogenousPolynomial),
            "Computes derivative and hessian of the map at a vector 'u' "
            "that was send to any vector or function evaluating value. "
            "In this case computation can be speeded up.")
        .def("homogenousPolynomial", py::overload_cast<JetType&, IMap::size_type>
            (&IMap::homogenousPolynomial<JetType>, py::const_),
            "Computes jet to degree 'degree' of the map at a vector 'u', "
            "at which the map was previously evaluated. "
            "In this case computation can be speeded up.")
        .def("__call__", py::overload_cast<const VectorType&, MatrixType&, HessianType&>
            (&IMap::operator(), py::const_),
            "computes value, first and second order derivatives for a given vector.")
        .def("__call__", py::overload_cast<ScalarType, const VectorType&, MatrixType&, HessianType&>
            (&IMap::operator(), py::const_),
            "computes value, first and second order derivatives for a given vector and time.")
        .def("__call__", py::overload_cast<const JetType&>(&IMap::operator(), py::const_),
            "computes propagation of the jet x through the map and returns jet of "
            "normalized partial derivatives of the function f∘x. "
            "Note if R^N->R^M with N≠M then input and output jets have different dimensions.")
        .def("__call__", py::overload_cast<ScalarType, const JetType&>(&IMap::operator(), py::const_),
            "computes propagation of the jet x through the map and returns jet of "
            "normalized partial derivatives of the function f∘x. "
            "Note if R^N->R^M with N≠M then input and output jets have different dimensions.")
        .def("__call__", py::overload_cast<const VectorType&, JetType&>
            (&IMap::operator(), py::const_))
        .def("__call__", py::overload_cast<ScalarType, const VectorType&, JetType&>
            (&IMap::operator(), py::const_))
        .def("computeODECoefficients",
        [](IMap& self, std::vector<VectorType>& coeffs, IMap::size_type order) {
            self.computeODECoefficients(coeffs.data(), order);
        }, "iterative computation of Taylor coefficients up to given order for a solution to ODE "
            "represented by this map. "
            "order - order of Taylor method (degree of polynomial approximation to the solution). "
            "coeffs[0] - initial condition for ODE must be the first vector in the table. "
            "coeffs[1],...,coeffs[order] - computed coefficients of polynomial approximation.")
        .def("computeODECoefficients", [](IMap& self,
            std::vector<VectorType>& coeffs,
            std::vector<MatrixType>& dCoeffs,
            IMap::size_type order) {
            self.computeODECoefficients(coeffs.data(), dCoeffs.data(), order);
        }, "iterative computation of Taylor coefficients up to given order for a solution to ODE "
            "represented by this map together with first order variational equations. "
            "order - order of Taylor method (degree of polynomial approximation to the solution). "
            "coeffs[0] - initial condition for ODE must be the first vector in the table. "
            "coeffs[1],...,coeffs[order] - computed coefficients of polynomial approximation. "
            "dCoeffs[0] - initial condition for variational equation. "
            "dCoeffs[1],...,dCoeffs[order] - computed coefficients of polynomial approximation "
            "to the solution to variational equation.")
        .def("computeODECoefficients", [](IMap& self,
                std::vector<VectorType>& coeffs,
                std::vector<MatrixType>& dCoeffs,
                std::vector<HessianType>& hCoeffs,
                IMap::size_type order) {
            self.computeODECoefficients(coeffs.data(), dCoeffs.data(), hCoeffs.data(), order);
        }, "iterative computation of Taylor coefficients up to given order for a solution to ODE "
            "represented by this map together with first and second order variational equations. "
            "order - order of Taylor method (degree of polynomial approximation to the solution). "
            "coeffs[0] - initial condition for ODE must be the first vector in the table. "
            "coeffs[1],...,coeffs[order] - computed coefficients of polynomial approximation. "
            "dCoeffs[0] - initial condition for variational equation. "
            "dCoeffs[1],...,dCoeffs[order] - computed coefficients of polynomial approximation "
            "to the solution to variational equation. "
            "hCoeffs[0] - initial condition for second order variational equation. "
            "hCoeffs[1],...,hCoeffs[order] - computed coefficients of polynomial approximation "
            "to the solution to second order variational equation. "
            "Second order variational equations are written "
            "in the base of normalized derivatives (Taylor coefficients). "
            "To obtain derivatives of solution wrt to initial condition "
            "one must multiply them by suitable factorials.")
        .def("computeODECoefficients", [](IMap& self,
            std::vector<JetType>& coeffs,
            IMap::size_type degree,
            IMap::size_type order) {
            self.computeODECoefficients(coeffs.data(), degree, order);
        }, "Iterative computation of Taylor coefficients up to given order for a solution to ODE "
            "and its variational equations. "
            "degree - The maximal order of derivatives with respect to "
            "initial conditions is specified by this argument"
            "order - order of Taylor method (degree of polynomial approximation to the solution)"
            "coeffs[0] - jets of initial conditions for the solution and all variational equations,"
            "coeffs[1],...,coeffs[order] - computed coefficients  of polynomial approximation "
            "to the solution all variational equations"
            "coeffs[i] can be a jet of degree bigger than the argument 'degree'.")
        .def("setParameters", &IMap::setParameters,
            "simultaneously sets values of many parameters. "
            "It is assumed that given vector contains values of subsequent parameters.")
        .def("degree", &IMap::degree,
            "returns maximal possible order of space-derivative that the map can compute by this map. "
            "Specified by the user in the constructor (default value is 1).")
        .def("setDegree", &IMap::setDegree,
            "set maximal order of space-derivatives that the map can compute.")
        ;
}