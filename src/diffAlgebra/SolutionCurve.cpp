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
        ;
}