#include <capd/poincare/BasicPoincareMap.hpp>

void wrapCrossingDirection(pybind11::module& mod)
{
    namespace py = pybind11;
    using namespace capd::poincare;

    py::native_enum<CrossingDirection>(mod, "CrossingDirection", "enum.Enum")
        .value("PlusMinus", PlusMinus)
        .value("Both", Both)
        .value("MinusPlus", MinusPlus)
        .finalize()
        ;
}

template<typename SolverType, bool wrapComputeDP = false>
void wrapBasicPoincareMap(pybind11::module& mod, const std::string& name)
{
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::poincare;
    using BasicPoincareMapType = BasicPoincareMap<SolverType>;
    using SectionType = BasicPoincareMapType::SectionType;
    using VectorType = BasicPoincareMapType::VectorType;
    using MatrixType = BasicPoincareMapType::MatrixType;
    using ScalarType = BasicPoincareMapType::ScalarType;
    using RealType = BasicPoincareMapType::RealType;
    using HessianType = BasicPoincareMapType::HessianType;
    using JetType = BasicPoincareMapType::JetType;

    py::class_<BasicPoincareMapType> bp(mod, name.c_str());
    bp.def(py::init<SolverType&, SectionType&, CrossingDirection, const RealType&>(),
            py::arg("solver"), py::arg("section"), py::arg("direction") = Both,
            py::arg_v("errorTolerance", pow(TypeTraits<RealType>::epsilon(), RealType(14.)/RealType(15.)),
            "epsilon^(14/15)"))
        .def("__call__", py::overload_cast<const VectorType&>(&BasicPoincareMapType::operator()),
            "Computes value of Poincare Map.",
            py::arg("v"))
        .def("__call__", py::overload_cast<VectorType, ScalarType&>(&BasicPoincareMapType::operator()),
            "Computes value of Poincare Map.",
            py::arg("v"), py::arg("in_out_time"))
        .def("__call__", py::overload_cast<VectorType, VectorType&, ScalarType&>(&BasicPoincareMapType::operator()),
            "Computes value of Poincare Map.",
            py::arg("v"), py::arg("afterSection"), py::arg("in_out_time"))
        .def("__call__", py::overload_cast<const VectorType&, MatrixType&>(&BasicPoincareMapType::operator()),
            "Computes value of Poincare Map and derivative of the flow.",
            py::arg("v"), py::arg("dF"))
        .def("__call__", py::overload_cast<VectorType, MatrixType&, ScalarType&>(&BasicPoincareMapType::operator()),
            "Computes value of Poincare Map and derivative of the flow.",
            py::arg("v"), py::arg("dF"), py::arg("in_out_time"))
        .def("__call__", py::overload_cast<const VectorType&, MatrixType&, HessianType&>(&BasicPoincareMapType::operator()),
            "Computes value of Poincare Map, derivative and hessian of the flow.",
            py::arg("v"), py::arg("dF"), py::arg("h"))
        .def("__call__", py::overload_cast<VectorType, MatrixType&, HessianType&, ScalarType&>
            (&BasicPoincareMapType::operator()),
            "Computes value of Poincare Map, derivative and hessian of the flow.",
            py::arg("v"), py::arg("dF"), py::arg("h"), py::arg("in_out_time"))
        .def("__call__", py::overload_cast<JetType&>(&BasicPoincareMapType::operator()),
            "Computes Poincare Map and derivatives of the flow to given order evaluated at return time. "
            "This routine is valid for an autonomous flows, only.")
        .def("__call__", py::overload_cast<JetType&, ScalarType&>(&BasicPoincareMapType::operator()),
            "Computes Poincare Map and derivatives of the flow to given order evaluated at return time. "
            "This routine is valid for both autonomous and time-dependent vector fields.",
            py::arg("x"), py::arg("in_out_time"))
        .def("computeDP", static_cast<MatrixType (BasicPoincareMapType::*)
            (const VectorType&, const MatrixType&, VectorType&, ScalarType)>
            (&BasicPoincareMapType::computeDP),
            "Simultaneous computation of gradient of return time and derivative of Poincare Map dP.",
            py::arg("Px"), py::arg("derivativeOfFlow"), py::arg("dT"),
            py::arg("returnTime") = TypeTraits<ScalarType>::zero())
        .def("computeDP", static_cast<MatrixType (BasicPoincareMapType::*)
            (const VectorType&, const MatrixType&, ScalarType)>
            (&BasicPoincareMapType::computeDP),
            "Computes derivative of Poincare Map dP.",
            py::arg("Px"), py::arg("derivativeOfFlow"), py::arg("returnTime") = TypeTraits<ScalarType>::zero())
        .def("computeDP", static_cast<void (BasicPoincareMapType::*)
            (const VectorType&, const MatrixType&, const HessianType&,
                MatrixType&, HessianType&, VectorType&, MatrixType&, ScalarType)>
            (&BasicPoincareMapType::computeDP),
            "Simultaneous computation of first and second Taylor coefficients of return time and Poincare map.",
            py::arg("Px"), py::arg("derivativeOfFlow"), py::arg("hessianOfFlow"), py::arg("DP"), py::arg("D2P"),
            py::arg("dT"), py::arg("d2T"), py::arg("returnTime") = TypeTraits<ScalarType>::zero())
        .def("computeDP", static_cast<void (BasicPoincareMapType::*)
            (const VectorType&, const MatrixType&, const HessianType&, MatrixType&, HessianType&, ScalarType)>
            (&BasicPoincareMapType::computeDP),
            "Simultaneous computation of first and second Taylor coefficients of return time and Poincare map.",
            py::arg("Px"), py::arg("derivativeOfFlow"), py::arg("hessianOfFlow"), py::arg("DP"), py::arg("D2P"),
            py::arg("returnTime") = TypeTraits<ScalarType>::zero())
        .def("getSolver", py::overload_cast<>(&BasicPoincareMapType::getSolver),
            "Returns read-only reference to solver used to integrate the system")
        .def("getVectorField", py::overload_cast<>(&BasicPoincareMapType::getVectorField),
            "Returns reference to solver used to integrate the system")
        .def("getSection", &BasicPoincareMapType::getSection,
            "Returns reference to Poincare section object")
        .def("getOrder", &BasicPoincareMapType::getOrder,
            "Returns order of numerical method used")
        .def("getStep", &BasicPoincareMapType::getStep,
            "Returns time step")
        .def("setOrder", &BasicPoincareMapType::setOrder,
            "Sets order of Taylor method")
        .def("setSection", &BasicPoincareMapType::setSection,
            "Sets new section function")
        .def("setStep", &BasicPoincareMapType::setStep,
            "Sets time step for integration of DS")
        .def("setFactor", &BasicPoincareMapType::setFactor)
        .def("setCrossingDirection", &BasicPoincareMapType::setCrossingDirection)
        .def("turnOnStepControl", &BasicPoincareMapType::turnOnStepControl,
            "Disables automatic step control")
        .def("turnOffStepControl", &BasicPoincareMapType::turnOffStepControl,
            "Enables automatic step control. Step control strategy is built in the solver.")
        .def("onOffStepControl", &BasicPoincareMapType::onOffStepControl,
            "Disables or enables automatic step control")
        .def("setMaxReturnTime", &BasicPoincareMapType::setMaxReturnTime,
            "Sets maximal return time to Poincare section. "
            "If the trajectory does not reach the section during time [0,maxReturnTime] then an exception is thrown. "
            "This prevents looping of the procedure computing Poincare map in the case when the trajectory "
            "is captured by an attractor (like sink or attracting periodic orbit) "
            "and never intersect Poincare section. "
            "Default value is maxReturnTime = 1000.")
        .def("setBlowUpMaxNorm", &BasicPoincareMapType::setBlowUpMaxNorm,
            "Sets threshold value of \f$ L_1\f$ norm that is considered as a blow up of the solution. "
            "A trajectory may escape to infinity in finite time without crossing Poincare section. "
            "If the \f$ L_1 \f$ norm of a point on trajectory is bigger than this threshold value "
            "then an exception is thrown. "
            "Default value is blowUpMaxNorm = 1e+10.")
        ;

        if constexpr(wrapComputeDP)
        {
            bp.def("computeDP", &BasicPoincareMapType::template computeDP<JetType>,
                "Recomputes Taylor expansion of the flow into Taylor expansion of Poincare map.");
        }
}