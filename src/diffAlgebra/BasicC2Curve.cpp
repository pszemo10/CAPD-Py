#include <capd/diffAlgebra/BasicC2Curve.h>

void wrapBasicC2Curve(pybind11::module_& mod){
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::diffAlgebra;
    using IMap = map::Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using IBasicC2Curve = BasicC2Curve<IMap::MatrixType>;
    using size_type = IBasicC2Curve::size_type;

    py::class_<IBasicC2Curve, BasicCurve<IMap::MatrixType>>(mod, "IBasicC2Curve")
        .def("setOrder", &IBasicC2Curve::setOrder)
        .def("clearCoefficients", &IBasicC2Curve::clearCoefficients)
        .def("coefficient", py::overload_cast<size_type, size_type, size_type, size_type>
            (&IBasicC2Curve::coefficient, py::const_))
        .def("remainderCoefficient", py::overload_cast<size_type, size_type, size_type, size_type>
            (&IBasicC2Curve::remainderCoefficient, py::const_))
        .def("getHessianCoefficients", py::overload_cast<size_type>
            (&IBasicC2Curve::getHessianCoefficients, py::const_))
        .def("getHessianRemainderCoefficients", py::overload_cast<size_type>
            (&IBasicC2Curve::getHessianRemainderCoefficients, py::const_))
        .def("hessianCoefficientsIterator", [](IBasicC2Curve& c, size_type j){
            return py::make_iterator(c.beginHessianCoefficients(j), c.endHessianCoefficients(j));
        }, py::keep_alive<0, 1>())
        .def("hessianRemainderCoefficientsIterator", [](IBasicC2Curve& c, size_type j){
            return py::make_iterator(c.beginHessianRemainderCoefficients(j), c.endHessianRemainderCoefficients(j));
        }, py::keep_alive<0, 1>())
        .doc() = "This class is a data structure for storing of a parametric curve "
                "together with first and second order derivatives with respect to initial point. \n\n"
                "More precisely, a curve c(t,x) is represented as "
                "c(t,x_0) + d/dx c(t,x)(x-x_0) + smallRemainder(t,x) \n\n"
                "This class provides a member functions for accessing of all coefficients. \n\n"
                "This class is a basic class for more general C2Curve.) "
        ;
}