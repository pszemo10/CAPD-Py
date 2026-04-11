#include <capd/diffAlgebra/BasicCnCurve.h>

void wrapBasicCnCurve(pybind11::module_& mod)
{
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::diffAlgebra;
    using IMap = map::Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using IBasicCnCurve = BasicCnCurve<IMap::MatrixType>;
    using size_type = IBasicCnCurve::size_type;

    py::class_<IBasicCnCurve>(mod, "IBasicCnCurve")
        .def("setOrder", &IBasicCnCurve::setOrder,
            "Sets the order of Taylor interpolation")
        .def("getOrder", &IBasicCnCurve::getOrder,
            "Returns the order of Taylor interpolation")
        .def("getAllocatedOrder", &IBasicCnCurve::getAllocatedOrder,
            "Returns maximal allocated order - used to avoid memory reallocation")
        .def("dimension", &IBasicCnCurve::dimension,
            "Returns the dimension in which the parametric curve is embedded")
        .def("degree", &IBasicCnCurve::degree,
            "Returns maximal degree of the jet")
        .def("setDegree", &IBasicCnCurve::setDegree,
            "Sets new maximal degree of the jet and reallocates memory")
        .def("clearCoefficients", &IBasicCnCurve::clearCoefficients,
            "sets all coefficients to zero")
        .def("centerCoefficient", py::overload_cast<size_type, size_type>
            (&IBasicCnCurve::centerCoefficient, py::const_))
        .def("coefficient", py::overload_cast<size_type, size_type>
            (&IBasicCnCurve::coefficient, py::const_))
        .def("coefficient", py::overload_cast<size_type, size_type, size_type>
            (&IBasicCnCurve::coefficient, py::const_))
        .def("coefficient", py::overload_cast<size_type, size_type, size_type, size_type>
            (&IBasicCnCurve::coefficient, py::const_))
        .def("coefficient", py::overload_cast<size_type, size_type, size_type, size_type, size_type>
            (&IBasicCnCurve::coefficient, py::const_))
        .def("remainderCoefficient", py::overload_cast<size_type, size_type>
            (&IBasicCnCurve::remainderCoefficient, py::const_))
        .def("remainderCoefficient", py::overload_cast<size_type, size_type, size_type>
            (&IBasicCnCurve::remainderCoefficient, py::const_))
        .def("remainderCoefficient", py::overload_cast<size_type, size_type, size_type, size_type>
            (&IBasicCnCurve::remainderCoefficient, py::const_))
        .def("remainderCoefficient", py::overload_cast<size_type, size_type, size_type, size_type, size_type>
            (&IBasicCnCurve::remainderCoefficient, py::const_))
        ;
}