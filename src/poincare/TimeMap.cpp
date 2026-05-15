#include <capd/poincare/TimeMap.h>
#include <capd/dynset/lib.h>

template<typename SolverType, typename...Sets>
void wrapC0Sets(pybind11::class_<capd::poincare::TimeMap<SolverType>>& tm)
{
    using TimeMapType = capd::poincare::TimeMap<SolverType>;
    using VectorType = TimeMapType::VectorType;
    using ScalarType = TimeMapType::ScalarType;
    using SolutionCurve = TimeMapType::SolutionCurve;

    (..., tm.def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, Sets&)>(&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, Sets&, SolutionCurve&)>
            (&TimeMapType::operator())));
}

template<typename SolverType, typename...Sets>
void wrapC1C2CnSets(pybind11::class_<capd::poincare::TimeMap<SolverType>>& tm)
{
    using TimeMapType = capd::poincare::TimeMap<SolverType>;
    using VectorType = TimeMapType::VectorType;
    using MatrixType = TimeMapType::MatrixType;
    using ScalarType = TimeMapType::ScalarType;
    using SolutionCurve = TimeMapType::SolutionCurve;

    (..., tm.def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, Sets&, MatrixType&)>(&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, Sets&)>(&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, Sets&, SolutionCurve&)>
            (&TimeMapType::operator())));
}

template<typename SolverType, bool wrapHOSets = true>
void wrapTimeMap(pybind11::module& mod, const std::string& name)
{
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::poincare;
    using TimeMapType = TimeMap<SolverType>;
    using ScalarType = TimeMapType::ScalarType;
    using VectorType = TimeMapType::VectorType;
    using MatrixType = TimeMapType::MatrixType;
    using HessianType = TimeMapType::HessianType;
    using JetType = TimeMapType::JetType;
    using SolutionCurve = TimeMapType::SolutionCurve;
    using size_type = TimeMapType::size_type;

    py::class_<TimeMapType> tm(mod, name.c_str());
    tm.def(py::init<SolverType&>(), py::keep_alive<1, 2>())
        .def("__call__", static_cast<VectorType (TimeMapType::*) (ScalarType, VectorType&)>
            (&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, VectorType&, ScalarType&)>(&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, VectorType&, SolutionCurve&)>(&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, VectorType&, MatrixType&)>
            (&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, VectorType&, MatrixType&, ScalarType&)>
            (&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, VectorType&, MatrixType&, SolutionCurve&)>
            (&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, VectorType&, const MatrixType&, MatrixType&)>
            (&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, VectorType&, const MatrixType&, MatrixType&, ScalarType&)>
            (&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, VectorType&, const MatrixType&, MatrixType&, SolutionCurve&)>
            (&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, VectorType&, MatrixType&, HessianType&)>
            (&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, VectorType&, MatrixType&, HessianType&, ScalarType&)>
            (&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, VectorType&, MatrixType&, HessianType&, SolutionCurve&)>
            (&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, VectorType&, const MatrixType&, const HessianType&, MatrixType&, HessianType&)>
            (&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, VectorType&, const MatrixType&, const HessianType&, MatrixType&, HessianType&, ScalarType&)>
            (&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, VectorType&, const MatrixType&, const HessianType&, MatrixType&, HessianType&, SolutionCurve&)>
            (&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, VectorType&, JetType&)>
            (&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, VectorType&, JetType&, ScalarType&)>
            (&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, VectorType&, JetType&, SolutionCurve&)>
            (&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, const JetType&, JetType&)>
            (&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, const JetType&, JetType&, ScalarType&)>
            (&TimeMapType::operator()))
        .def("__call__", static_cast<VectorType (TimeMapType::*)
            (ScalarType, const JetType&, JetType&, SolutionCurve&)>
            (&TimeMapType::operator()))
        .def("getSolver", py::overload_cast<>(&TimeMapType::getSolver, py::const_))
        .def("getVectorField", py::overload_cast<>(&TimeMapType::getVectorField, py::const_))
        .def("getOrder", &TimeMapType::getOrder)
        .def("setOrder", &TimeMapType::setOrder)
        .def("getStep", &TimeMapType::getStep)
        .def("setStep", &TimeMapType::setStep)
        .def("turnOnStepControl", &TimeMapType::turnOnStepControl)
        .def("turnOffStepControl", &TimeMapType::turnOffStepControl)
        .def("onOffStepControl", &TimeMapType::onOffStepControl)
        .def("stopAfterStep", &TimeMapType::stopAfterStep)
        .def("completed", &TimeMapType::completed)
        .def("getCurrentTime", &TimeMapType::getCurrentTime);

    if constexpr(wrapHOSets)
    {
        wrapC0Sets<SolverType, C0Rect2Set, C0TripletonSet, C0HORect2Set, C0HOTripletonSet>(tm);
        wrapC1C2CnSets<SolverType, C1Rect2Set, C1HORect2Set, C11Rect2Set, C2Rect2Set, CnRect2Set>(tm);
    }
    else
    {
        wrapC0Sets<SolverType, C0Rect2Set, C0TripletonSet>(tm);
        wrapC1C2CnSets<SolverType, C1Rect2Set, C11Rect2Set, C2Rect2Set, CnRect2Set>(tm);
    }


}