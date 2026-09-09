#include <capd/diffAlgebra/SolutionCurve.h>

template<typename CurveType>
void wrapSolutionCurve(pybind11::module& mod, const std::string& baseName, const std::string& name)
{
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::diffAlgebra;
    using BaseSolutionCurveType = BaseSolutionCurve<CurveType>;
    using SolutionCurveType = SolutionCurve<CurveType>;

    py::class_<BaseSolutionCurveType, ParametricCurve<typename CurveType::MatrixType>>(mod, baseName.c_str())
        .def("getLeftDomain", &BaseSolutionCurveType::getLeftDomain)
        .def("getRightDomain", &BaseSolutionCurveType::getRightDomain)
        .def("add", &BaseSolutionCurveType::add)
        .def("getNumberOfPieces", &BaseSolutionCurveType::getNumberOfPieces)
        ;

    py::class_<SolutionCurveType, BaseSolutionCurveType>(mod, name.c_str())
        .def(py::init<typename SolutionCurveType::ScalarType>())
        .def("checkAndFind", &SolutionCurveType::checkAndFind)
        .def("timeDerivative", &SolutionCurveType::timeDerivative)
        .def("__call__", &SolutionCurveType::operator())
        .def("derivative", &SolutionCurveType::derivative)
        .def("hessian", &SolutionCurveType::hessian)
        .def("jet", &SolutionCurveType::jet)
        .doc() = "This is class that represents parametric curve in R^n. "
                "Internally it is represented by piecewise polynomial approximation. \n"
                "It can also store higher order partial derivatives with respect to space variables, i.e. \n"
                "c(t,x) can be a polynomial both with respect to main "
                "parameterization variable 't' and space variable 'x'. \n"
                "The curve can be evaluated at given time 't' as well as differentiated with respect to 't'. \n"
                "The curve can store rigorous enclosures of curves. "
                "They are represented using mean value form to reduce some wrapping effect."
        ;
}