#include <capd/diffAlgebra/C2Curve.h>
#include <capd/diffAlgebra/BasicC2Curve.h>

void wrapC2Curve(pybind11::module_& mod)
{
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::diffAlgebra;
    using IMap = map::Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using BaseCurve = BasicC2Curve<IMap::MatrixType>;
    using IC2Curve = C2Curve<BaseCurve>;
    using size_type = IC2Curve::size_type;

    py::class_<IC2Curve, Curve<BaseCurve>,
        BaseCurve, ParametricCurve<typename BaseCurve::MatrixType>>(mod, "IC2Curve")
        .def("hessian", &IC2Curve::hessian)
        .def("setInitHessian", &IC2Curve::setInitHessian)
        ;
}