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
    using size_type = typename IMap::size_type;


    py::class_<IMap, BasicFunction<ScalarType>>(mod, "IMap")
        .def(py::init<>())
        .def(py::init<const std::string&, size_type>(),
            "parses expression from given string. Allocates memory for jet propagation of degree 'degree'",
            py::arg("f"), py::pos_only(), py::arg("degree")=1)
        .def(py::init<const IMap&>(), "copying constructor")
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
        .def("homogenousPolynomial", py::overload_cast<JetType&, size_type>
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
        .def("computeODECoefficients", [](IMap& self, const VectorType& coeff, size_type order) {
            std::vector<VectorType> coeffs(order+1, VectorType(coeff.dimension()));
            coeffs[0] = coeff;
            self.computeODECoefficients(coeffs.data(), order);
            return coeffs;
        }, "iterative computation of Taylor coefficients up to given order for a solution to ODE "
            "represented by this map. "
            "order - order of Taylor method (degree of polynomial approximation to the solution). "
            "coeff - initial condition for ODE must be the first vector in the table. ")
        .def("computeODECoefficients", [](IMap& self,
            const VectorType& coeff, const MatrixType& dCoeff, size_type order)
        {
            std::vector<VectorType> coeffs(order+1, VectorType(coeff.dimension()));
            std::vector<MatrixType> dCoeffs(order+1, MatrixType(dCoeff.numberOfRows(), dCoeff.numberOfColumns()));
            coeffs[0] = coeff;
            dCoeffs[0] = dCoeff;
            self.computeODECoefficients(coeffs.data(), dCoeffs.data(), order);
            return std::make_tuple(coeffs, dCoeffs);
        }, "iterative computation of Taylor coefficients up to given order for a solution to ODE "
            "represented by this map together with first order variational equations. "
            "order - order of Taylor method (degree of polynomial approximation to the solution). "
            "coeff - initial condition for ODE must be the first vector in the table. "
            "dCoeff - initial condition for variational equation. ")
        .def("computeODECoefficients", [](IMap& self, const VectorType& coeff, const MatrixType& dCoeff,
            const HessianType& hCoeff, IMap::size_type order)
        {
            std::vector<VectorType> coeffs(order+1, VectorType(coeff.dimension()));
            std::vector<MatrixType> dCoeffs(order+1, MatrixType(dCoeff.numberOfRows(), dCoeff.numberOfColumns()));
            std::vector<HessianType> hCoeffs(order+1, HessianType(hCoeff.imageDimension(), hCoeff.dimension()));
            coeffs[0] = coeff;
            dCoeffs[0] = dCoeff;
            hCoeffs[0] = hCoeff;

            self.computeODECoefficients(coeffs.data(), dCoeffs.data(), hCoeffs.data(), order);
            return std::make_tuple(coeffs, dCoeffs, hCoeffs);
        }, "iterative computation of Taylor coefficients up to given order for a solution to ODE "
            "represented by this map together with first and second order variational equations. "
            "order - order of Taylor method (degree of polynomial approximation to the solution). "
            "coeff - initial condition for ODE must be the first vector in the table. "
            "dCoeff - initial condition for variational equation. "
            "hCoeff - initial condition for second order variational equation. "
            "Second order variational equations are written "
            "in the base of normalized derivatives (Taylor coefficients). "
            "To obtain derivatives of solution wrt to initial condition "
            "one must multiply them by suitable factorials.")
        .def("computeODECoefficients", [](IMap& self, JetType& coeff, size_type degree, size_type order) {
            std::vector<JetType> coeffs(order+1, JetType(coeff.imageDimension(), coeff.dimension(), coeff.degree()));
            coeffs[0] = coeff;
            self.computeODECoefficients(coeffs.data(), degree, order);
            return coeffs;
        }, "Iterative computation of Taylor coefficients up to given order for a solution to ODE "
            "and its variational equations. "
            "degree - The maximal order of derivatives with respect to "
            "initial conditions is specified by this argument"
            "order - order of Taylor method (degree of polynomial approximation to the solution)"
            "coeff - jet of initial conditions for the solution and all variational equations,"
            "returned coeffs can be a jet of degree bigger than the argument 'degree'.")
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