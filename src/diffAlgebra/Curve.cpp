#include <capd/diffAlgebra/Curve.h>

template <class BaseCurveT>
void wrapCurve(pybind11::module& mod, const std::string& name)
{
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::diffAlgebra;
    using IMap = map::Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using ICurve = Curve<BaseCurveT>;
    using size_type = ICurve::size_type;
    using Real = ICurve::Real;

    py::class_<ICurve, BaseCurveT, ParametricCurve<typename BaseCurveT::MatrixType>>
        (mod, name.c_str())
        .def(py::init<Real, Real, size_type, size_type, size_type>())
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
        .doc() = "This class provides methods for evaluation of the parametric curve "
                "for a given parameter value."
        ;
}