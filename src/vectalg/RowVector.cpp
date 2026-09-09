#include <capd/vectalg/RowVector.h>

void wrapRowVector(pybind11::module &mod){
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::vectalg;
    using IRowVector = RowVector<capd::interval, CAPD_DEFAULT_DIMENSION>;
    using ScalarType = IRowVector::ScalarType;
    using IVector = Vector<ScalarType, CAPD_DEFAULT_DIMENSION>;

    py::class_<IRowVector>(mod, "IRowVector")
        .def(py::self += py::self)
        .def(py::self += IVector())
        .def(py::self -= py::self)
        .def(py::self -= IVector())
        .def(py::self *= ScalarType())
        .def(py::self /= ScalarType())
        .def("__setitem__", [](IRowVector &v, int index, const ScalarType &value) { v[index] = value; })
        .def("__getitem__", [](const IRowVector &v, int index) { return v[index]; })
        .def("euclNorm", &IRowVector::euclNorm)
        .def("normalize", &IRowVector::normalize)
        .def("clear", &IRowVector::clear)
        .def("dimension", &IRowVector::dimension)
        .def("__iter__", [](const IRowVector &rv) {
            return py::make_iterator(rv.begin(), rv.end());
        }, py::keep_alive<0, 1>())
        .def("assertEqualSize", &IRowVector::assertEqualSize)
        .def(IVector() + py::self)
        .def(py::self + IVector())
        .def(py::self + py::self)
        .def(IVector() - py::self)
        .def(py::self - IVector())
        .def(py::self - py::self)
        .def("__matmul__", [](const IVector &v1, const IRowVector &v2) { return v1*v2; })
        .def("__matmul__", [](const IRowVector &v1, const IVector &v2) { return v1*v2; })
        .def("__matmul__", [](const IRowVector &v1, const IRowVector &v2) { return v1*v2; })
        .def(-py::self)
        .def(ScalarType() * py::self)
        .def(py::self * ScalarType())
        .def(py::self / ScalarType())
        .def(py::self /= ScalarType())
        .def(py::self *= ScalarType())
        .def("__repr__",
            [](const IRowVector &rv) {
                std::ostringstream oss;
                oss << rv;
                return oss.str();
            })
        .doc() = "RowVector class realizes a vector without its own container. "
            "He is just a reference to a part of other object (i.e. Matrix of Vector) "
            "with his own container."
        ;
    
    mod.def("diam", &diam<ScalarType, CAPD_DEFAULT_DIMENSION>);
}