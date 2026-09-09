#include <capd/diffAlgebra/BasicCurve.h>

void wrapBasicCurve(pybind11::module& mod)
{
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::diffAlgebra;
    using IMap = map::Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using IBasicCurve = BasicCurve<IMap::MatrixType>;
    using VectorType = typename IBasicCurve::VectorType;
    using MatrixType = typename IBasicCurve::MatrixType;
    using ScalarType = typename IBasicCurve::ScalarType;
    using size_type = typename IBasicCurve::size_type;

    py::class_<IBasicCurve, std::unique_ptr<IBasicCurve, py::nodelete>>(mod, "BasicCurve")
        .def("setOrder", &IBasicCurve::setOrder, "Sets the order of Taylor interpolation")
        .def("getOrder", &IBasicCurve::getOrder, "Returns the order of Taylor interpolation")
        .def("getAllocatedOrder", &IBasicCurve::getAllocatedOrder,
            "Returns maximal allocated order - used to avoid memory reallocation")
        .def("dimension", &IBasicCurve::dimension, "Returns the dimension in which the parametric curve is embedded")
        .def("clearCoefficients", &IBasicCurve::clearCoefficients, "sets all coefficients to zero")
        .def("centerCoefficient", py::overload_cast<size_type, size_type>
            (&IBasicCurve::centerCoefficient, py::const_))
        .def("coefficient", py::overload_cast<size_type, size_type>
            (&IBasicCurve::coefficient, py::const_))
        .def("remainderCoefficient", py::overload_cast<size_type, size_type>
            (&IBasicCurve::remainderCoefficient, py::const_))
        .def("coefficient", py::overload_cast<size_type, size_type, size_type>
            (&IBasicCurve::coefficient, py::const_))
        .def("remainderCoefficient", py::overload_cast<size_type, size_type, size_type>
            (&IBasicCurve::remainderCoefficient, py::const_))
        .def("centerCoefficientsIterator", [](IBasicCurve& c, size_type j){
            return py::make_iterator(c.beginCenterCoefficients(j), c.endCenterCoefficients(j));
        }, py::keep_alive<0, 1>())
        .def("coefficientsIterator", [](IBasicCurve& c, size_type j){
            return py::make_iterator(c.beginCoefficients(j), c.endCoefficients(j));
        }, py::keep_alive<0, 1>())
        .def("remainderCoefficientsIterator", [](IBasicCurve& c, size_type j){
            return py::make_iterator(c.beginRemainderCoefficients(j), c.endRemainderCoefficients(j));
        }, py::keep_alive<0, 1>())
        .def("matrixCoefficientsIterator", [](IBasicCurve& c, size_type j){
            return py::make_iterator(c.beginMatrixCoefficients(j), c.endMatrixCoefficients(j));
        }, py::keep_alive<0, 1>())
        .def("matrixRemainderCoefficientsIterator", [](IBasicCurve& c, size_type j){
            return py::make_iterator(c.beginMatrixRemainderCoefficients(j), c.endMatrixRemainderCoefficients(j));
        }, py::keep_alive<0, 1>())
        .doc() = "This class is a data structure for storing of a parametric curve "
                "together with first order derivatives with respect to initial point.\n\n "
                "More precisely, a curve c(t,x) is represented as "
                "c(t,x_0) + d/dx c(t,x)(x-x_0) + smallRemainder(t,x)\n\n "
                "This class provides a member functions for accessing of all coefficients.\n\n "
                "This class is a basic class for more general Curve. "
        ;
}