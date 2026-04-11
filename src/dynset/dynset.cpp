#include <capd/dynset/lib.h>

void wrapDynset(pybind11::module& mod) {
    namespace py = pybind11;
    using namespace capd;
    using MatrixType = capd::IMatrix;
    using ScalarType = MatrixType::ScalarType;
    using VectorType = MatrixType::RowVectorType;

    py::class_<C0Rect2Set>(mod, "C0Rect2Set")
        .def(py::init<const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("r"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&,
            const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("B"),py::arg("r"),
            py::arg("t")=TypeTraits<ScalarType>::zero())
        ;

    py::class_<C0TripletonSet>(mod, "C0TripletonSet")
        .def(py::init<const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("r"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&,
            const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("B"),py::arg("r"),
            py::arg("t")=TypeTraits<ScalarType>::zero())
        ;

    py::class_<C0HORect2Set>(mod, "C0HORect2Set")
        .def(py::init<const C0HOTripletonSet::C0BaseSet&>())
        .def(py::init<const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("r"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&,
            const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("B"),py::arg("r"),
            py::arg("t")=TypeTraits<ScalarType>::zero())
        ;

    py::class_<C0HOTripletonSet>(mod, "C0HOTripletonSet")
        .def(py::init<const C0HOTripletonSet::C0BaseSet&>())
        .def(py::init<const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("r"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&,
            const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("B"),py::arg("r"),
            py::arg("t")=TypeTraits<ScalarType>::zero())
        ;

    py::class_<C1Rect2Set>(mod, "C1Rect2Set")
        .def(py::init<const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("r"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&,
            const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("B"),py::arg("r"),
            py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const C1Rect2Set::C0BaseSet&, const C1Rect2Set::C1BaseSet&, ScalarType>(),
             py::arg("c0part"), py::arg("c1part"), py::arg("t")=TypeTraits<ScalarType>::zero())
        ;

    py::class_<C11Rect2Set>(mod, "C11Rect2Set")
        .def(py::init<const C11Rect2Set::BaseSet&>())
        ;

    py::class_<C1HORect2Set>(mod, "C1HORect2Set")
        .def(py::init<const C1HORect2Set::C0BaseSet&, const C1HORect2Set::C1BaseSet&, ScalarType>(),
             py::arg("c0part"), py::arg("c1part"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("r"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&,
            const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("B"),py::arg("r"),
            py::arg("t")=TypeTraits<ScalarType>::zero())
        ;

    py::class_<C2Rect2Set>(mod, "C2Rect2Set")
        .def(py::init<const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("r"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&,
            const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("B"),py::arg("r"),
            py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const C2Rect2Set::C0BaseSet&, const C2Rect2Set::C1BaseSet&, ScalarType>(),
            py::arg("c0part"), py::arg("c1part"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const C2Rect2Set::C0BaseSet&, const C2Rect2Set::C1BaseSet&,
            const C2Rect2Set::HessianType&, ScalarType>(),
            py::arg("c0part"), py::arg("c1part"), py::arg("hessian"), py::arg("t")=TypeTraits<ScalarType>::zero())
        ;

    py::class_<CnRect2Set>(mod, "CnRect2Set")
        .def(py::init<const VectorType&, CnRect2Set::size_type, ScalarType>(),
             py::arg("x"), py::arg("degree"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const VectorType&, CnRect2Set::size_type, ScalarType>(),
             py::arg("x"), py::arg("r0"), py::arg("degree"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, CnRect2Set::size_type, ScalarType>(),
             py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("degree"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, const VectorType&, CnRect2Set::size_type, ScalarType>(),
             py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("r"), py::arg("degree"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&,
            const MatrixType&, const VectorType&, CnRect2Set::size_type, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("B"),py::arg("r"),
            py::arg("degree"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const CnRect2Set::JetType&, ScalarType>(),
             py::arg("x"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const CnRect2Set::JetType&, const MatrixType&, const VectorType&, ScalarType>(),
             py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        ;
}