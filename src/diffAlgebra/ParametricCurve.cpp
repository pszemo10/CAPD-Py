#include <capd/diffAlgebra/ParametricCurve.h>
#include <capd/diffAlgebra/BasicCurve.h>

template <class MatrixT>
void wrapParametricCurve(pybind11::module& mod, const std::string& name)
{
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::diffAlgebra;
    using IMap = map::Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using MatrixType = BasicCurve<IMap::MatrixType>::MatrixType;
    using VectorType = MatrixType::RowVectorType;
    using IParametricCurve = ParametricCurve<MatrixType, VectorType>;

    py::class_<IParametricCurve, std::unique_ptr<IParametricCurve, py::nodelete>>
        (mod, name.c_str())
        .def("setDomain", &IParametricCurve::setDomain)
        .def("getLeftDomain", &IParametricCurve::getLeftDomain)
        .def("getRightDomain", &IParametricCurve::getRightDomain)
        .doc() = "This is an abstract class that represents parametric curve in R^n. "
                "We do not specify how it is represented in the memory \n."
                "The curve can be evaluated at given time 't' as well as differentiated with respect to 't' \n."
                "The curve can store rigorous enclosures of curves."
        ;
}