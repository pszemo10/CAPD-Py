#include <capd/poincare/PoincareMap.hpp>
#include <capd/dynset/lib.h>

template<typename SolverType, typename Set>
void wrapC0Methods(pybind11::class_<
    capd::poincare::PoincareMap<SolverType>, 
    capd::poincare::BasicPoincareMap<SolverType>>& pm)
{
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::poincare;
    using PoincareMapType = PoincareMap<SolverType>;
    using SectionType = PoincareMapType::SectionType;
    using VectorType = PoincareMapType::VectorType;
    using MatrixType = PoincareMapType::MatrixType;
    using ScalarType = PoincareMapType::ScalarType;
    using BoundType = PoincareMapType::BoundType;
    using HessianType = PoincareMapType::HessianType;
    using JetType = PoincareMapType::JetType;

    pm.def("__call__", static_cast<VectorType (PoincareMapType::*)
        (Set&, const VectorType&, const MatrixType&, ScalarType&, int)>
        (&PoincareMapType::operator()),
        "Computes value of n-th iterate of the Poincare Map. "
        "The result is returned in given affine coordinate system.",
        py::arg("set"), py::arg("x0"), py::arg("a"), py::arg("out_returnTime"), py::arg("n") = 1)
    .def("__call__", static_cast<VectorType (PoincareMapType::*)
        (Set&, ScalarType&, int)>
        (&PoincareMapType::operator()),
        "Computes value of n-th iterate of the Poincare Map (used for C^0 sets) and returns bound of return time",
        py::arg("set"), py::arg("out_returnTime"), py::arg("n") = 1)
    .def("__call__", static_cast<VectorType (PoincareMapType::*)
        (Set&, int)>
        (&PoincareMapType::operator()),
        "Computes value of n-th iterate of the Poincare Map (used for C^0 sets)",
        py::arg("set"), py::arg("n") = 1)
    ;
}

template<typename SolverType, typename... Sets>
void wrapC0(pybind11::class_<
    capd::poincare::PoincareMap<SolverType>, 
    capd::poincare::BasicPoincareMap<SolverType>>& pm)
{
    (..., wrapC0Methods<SolverType, Sets>(pm));
}

template<typename SolverType, typename Set>
void wrapC1Methods(pybind11::class_<
    capd::poincare::PoincareMap<SolverType>, 
    capd::poincare::BasicPoincareMap<SolverType>>& pm)
{
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::poincare;
    using PoincareMapType = PoincareMap<SolverType>;
    using SectionType = PoincareMapType::SectionType;
    using VectorType = PoincareMapType::VectorType;
    using MatrixType = PoincareMapType::MatrixType;
    using ScalarType = PoincareMapType::ScalarType;
    using BoundType = PoincareMapType::BoundType;
    using HessianType = PoincareMapType::HessianType;
    using JetType = PoincareMapType::JetType;

    pm.def("__call__", static_cast<VectorType (PoincareMapType::*)
        (Set&, const VectorType&, const MatrixType&, ScalarType&, int)>
        (&PoincareMapType::operator()),
        "Computes value of n-th iterate of the Poincare Map. "
        "The result is returned in given affine coordinate system.",
        py::arg("set"), py::arg("x0"), py::arg("a"), py::arg("out_returnTime"), py::arg("n") = 1)
    .def("__call__", static_cast<VectorType (PoincareMapType::*)
        (Set&, MatrixType&, ScalarType&, int)>
        (&PoincareMapType::operator()),
        "Computes value of n-th iterate of Poincare Map and derivatives of the flow  (used for C^1 sets)",
        py::arg("set"), py::arg("dF"), py::arg("out_returnTime"), py::arg("n") = 1)
    .def("__call__", static_cast<VectorType (PoincareMapType::*)
        (Set&, MatrixType&, int)>
        (&PoincareMapType::operator()),
        "Computes value of n-th iterate of Poincare Map and derivatives of the flow  (used for C^1 sets)",
        py::arg("set"), py::arg("dF"), py::arg("n") = 1)
    .doc() = "PoincareMap class rigorously computes Poincare Map. \n"
            "For given Dynamical System and section it rigorously computes first return map "
            "to section (Poincare Map) and its derivatives."
    ;
}

template<typename SolverType, typename... Sets>
void wrapC1(pybind11::class_<
    capd::poincare::PoincareMap<SolverType>, 
    capd::poincare::BasicPoincareMap<SolverType>>& pm)
{
    (..., wrapC1Methods<SolverType, Sets>(pm));
}

template<typename SolverType, typename Set>
void wrapC2Methods(pybind11::class_<
    capd::poincare::PoincareMap<SolverType>, 
    capd::poincare::BasicPoincareMap<SolverType>>& pm)
{
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::poincare;
    using PoincareMapType = PoincareMap<SolverType>;
    using SectionType = PoincareMapType::SectionType;
    using VectorType = PoincareMapType::VectorType;
    using MatrixType = PoincareMapType::MatrixType;
    using ScalarType = PoincareMapType::ScalarType;
    using BoundType = PoincareMapType::BoundType;
    using HessianType = PoincareMapType::HessianType;
    using JetType = PoincareMapType::JetType;

    pm.def("__call__", static_cast<VectorType (PoincareMapType::*)
        (Set&, const VectorType&, const MatrixType&, ScalarType&, int)>
        (&PoincareMapType::operator()),
        "Computes value of n-th iterate of the Poincare Map. "
        "The result is returned in given affine coordinate system.",
        py::arg("set"), py::arg("x0"), py::arg("a"), py::arg("out_returnTime"), py::arg("n") = 1)
    .def("__call__", static_cast<VectorType (PoincareMapType::*)
        (Set&, MatrixType&, HessianType&, int)>
        (&PoincareMapType::operator()),
        "Computes value of n-th iterate of Poincare Map, derivatives and hessian of the flow (used for C^2 sets)",
        py::arg("set"), py::arg("dF"), py::arg("hessian"), py::arg("n") = 1)
    .def("__call__", static_cast<VectorType (PoincareMapType::*)
        (Set&, MatrixType&, HessianType&, ScalarType&, int)>
        (&PoincareMapType::operator()),
        "Computes value of n-th iterate of Poincare Map, derivatives and hessian of the flow (used for C^2 sets)",
        py::arg("set"), py::arg("dF"), py::arg("hessian"), py::arg("out_returnTime"), py::arg("n") = 1)
    ;
}

template<typename SolverType, typename... Sets>
void wrapC2(pybind11::class_<
    capd::poincare::PoincareMap<SolverType>, 
    capd::poincare::BasicPoincareMap<SolverType>>& pm)
{
    (..., wrapC2Methods<SolverType, Sets>(pm));
}

template<typename SolverType, typename Set>
void wrapCnMethods(pybind11::class_<
    capd::poincare::PoincareMap<SolverType>, 
    capd::poincare::BasicPoincareMap<SolverType>>& pm)
{
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::poincare;
    using PoincareMapType = PoincareMap<SolverType>;
    using SectionType = PoincareMapType::SectionType;
    using VectorType = PoincareMapType::VectorType;
    using MatrixType = PoincareMapType::MatrixType;
    using ScalarType = PoincareMapType::ScalarType;
    using BoundType = PoincareMapType::BoundType;
    using HessianType = PoincareMapType::HessianType;
    using JetType = PoincareMapType::JetType;

    pm.def("__call__", static_cast<VectorType (PoincareMapType::*)
        (Set&, typename Set::JetType&, int)>
        (&PoincareMapType::operator()),
        "Computes n-th iterate of Poincare Map and derivatives of the flow to given order (used for C^n sets)",
        py::arg("set"), py::arg("result"), py::arg("n") = 1)
    .def("__call__", static_cast<VectorType (PoincareMapType::*)
        (Set&, typename Set::JetType&, ScalarType&, int)>
        (&PoincareMapType::operator()),
        "Computes n-th iterate of Poincare Map and derivatives of the flow to given order (used for C^n sets)",
        py::arg("set"), py::arg("result"), py::arg("out_returnTime"), py::arg("n") = 1)
    ;
}

template<typename SolverType, typename... Sets>
void wrapCn(pybind11::class_<
    capd::poincare::PoincareMap<SolverType>, 
    capd::poincare::BasicPoincareMap<SolverType>>& pm)
{
    (..., wrapCnMethods<SolverType, Sets>(pm));
}

template<typename SolverType, bool wrapHOSets = true>
void wrapPoincareMap(pybind11::module& mod, const std::string& name)
{
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::poincare;
    using PoincareMapType = PoincareMap<SolverType>;
    using SectionType = PoincareMapType::SectionType;
    using VectorType = PoincareMapType::VectorType;
    using MatrixType = PoincareMapType::MatrixType;
    using ScalarType = PoincareMapType::ScalarType;
    using BoundType = PoincareMapType::BoundType;
    using HessianType = PoincareMapType::HessianType;
    using JetType = PoincareMapType::JetType;

    py::class_<PoincareMapType, BasicPoincareMap<SolverType>> pm(mod, name.c_str());
    pm.def(py::init<SolverType&, SectionType&, CrossingDirection, const BoundType&>(),
            "Constructs PoincareMap for given dynamical system and section",
            py::arg("solver"), py::arg("section"), py::arg("direction") = Both, py::arg("errorTolerance") = 0.1)
        .def("__call__", static_cast<VectorType (PoincareMapType::*)
            (const VectorType&, const VectorType&, const MatrixType&, ScalarType&, int)>
            (&PoincareMapType::operator()),
            "Computes value of n-th iterate of the Poincare Map. "
            "The result is returned in given affine coordinate system.",
            py::arg("x"), py::arg("x0"), py::arg("A"), py::arg("out_returnTime"), py::arg("n") = 1)
        .def("__call__", static_cast<VectorType (PoincareMapType::*) (const VectorType&, ScalarType&, int)>
            (&PoincareMapType::operator()),
            "Computes value of n-th iterate of the Poincare Map (used for C^0 sets) and returns bound of return time",
            py::arg("x"), py::arg("out_returnTime"), py::arg("n") = 1)
        .def("__call__", static_cast<VectorType (PoincareMapType::*) (VectorType, int)>
            (&PoincareMapType::operator()),
            "Computes value of n-th iterate of the Poincare Map",
            py::arg("x"), py::arg("n") = 1)
        .def("__call__", static_cast<VectorType (PoincareMapType::*)
            (const VectorType&, MatrixType&, ScalarType&, int)>
            (&PoincareMapType::operator()),
            "Computes value of n-th iterate of Poincare Map and derivatives of the flow  (used for C^1 sets)",
            py::arg("x"), py::arg("dF"), py::arg("out_returnTime"), py::arg("n") = 1)
        .def("__call__", static_cast<VectorType (PoincareMapType::*) (const VectorType&, MatrixType&, int)>
            (&PoincareMapType::operator()),
            "Computes value of n-th iterate of Poincare Map and derivatives of the flow  (used for C^1 sets)",
            py::arg("x"), py::arg("dF"), py::arg("n") = 1)
        .def("getSectionDerivativesEnclosure", &PoincareMapType::getSectionDerivativesEnclosure)
        ;

    if constexpr(wrapHOSets)
    {
        wrapC0<SolverType, C0Rect2Set, C0TripletonSet, C0HORect2Set, C0HOTripletonSet>(pm);
        wrapC1<SolverType, C1Rect2Set, C1HORect2Set, C11Rect2Set>(pm);
    }
    else
    {
        wrapC0<SolverType, C0Rect2Set, C0TripletonSet>(pm);
        wrapC1<SolverType, C1Rect2Set, C11Rect2Set>(pm);
    }
    wrapC2<SolverType, C2Rect2Set>(pm);
    wrapCn<SolverType, CnRect2Set>(pm);

}