#include <capd/diffAlgebra/Curve.h>

template <class BaseCurveT>
void wrapCurve(pybind11::module& mod, const std::string& name)
{
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::diffAlgebra;
    using IMap = map::Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using ICurve = Curve<BaseCurveT>;

    py::class_<ICurve, BaseCurveT, ParametricCurve<typename BaseCurveT::MatrixType>>
        (mod, name.c_str())
        .def("timeDerivative", &ICurve::timeDerivative)
        .def("__call__", &ICurve::operator())
        .def("derivative", &ICurve::derivative)
        .def("__getitem__", &ICurve::operator[])
        .def("setInitMatrix", &ICurve::setInitMatrix)
        .def("oneStepDerivative", &ICurve::oneStepDerivative)
        .def("oneStepDerivativeOfNumericalMethod", &ICurve::oneStepDerivativeOfNumericalMethod)
        .def("valueAtCenter", &ICurve::valueAtCenter)
        .def("remainder", &ICurve::remainder)
        .def("getCenter", &ICurve::getCenter)
        ;
}