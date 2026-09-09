#include <capd/diffAlgebra/CnCurve.h>

void wrapCnCurve(pybind11::module_& mod)
{
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::diffAlgebra;
    using IMap = map::Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using BaseCurve = BasicCnCurve<IMap::MatrixType>;
    using ICnCurve = CnCurve<BaseCurve>;
    using size_type = ICnCurve::size_type;
    using Real = ICnCurve::Real;

    py::class_<ICnCurve, Curve<BaseCurve>,
        BaseCurve, ParametricCurve<typename BaseCurve::MatrixType>>(mod, "ICnCurve")
        .def(py::init<Real, Real, size_type, size_type, size_type>())
        .def("hessian", &ICnCurve::hessian)
        .def("setInitHessian", &ICnCurve::setInitHessian)
        .def("setInitJet", &ICnCurve::setInitJet)
        .def("eval", &ICnCurve::eval)
        .def("jet", &ICnCurve::jet)
        .doc() = "This class provides methods for evaluation of the parametric curve "
                "for a given parameter value."
        ;
}