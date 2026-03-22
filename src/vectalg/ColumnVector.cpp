#include <capd/vectalg/ColumnVector.h>

void wrapColumnVector(pybind11::module &mod){
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::vectalg;
    using IColumnVector = ColumnVector<capd::interval, CAPD_DEFAULT_DIMENSION>;
    using ScalarType = IColumnVector::ScalarType;
    using IVector = Vector<ScalarType, CAPD_DEFAULT_DIMENSION>;

    py::class_<IColumnVector>(mod, "IColumnVector")
        .def(py::self += py::self)
        .def(py::self += Vector<ScalarType, CAPD_DEFAULT_DIMENSION>())
        .def(py::self -= py::self)
        .def(py::self -= Vector<ScalarType, CAPD_DEFAULT_DIMENSION>())
        .def(py::self *= ScalarType())
        .def(py::self /= ScalarType())
        .def("__setitem__", [](IColumnVector &v, int index, const ScalarType &value) { v[index] = value; })
        .def("__getitem__", [](const IColumnVector &v, int index) { return v[index]; })
        .def("euclNorm", &IColumnVector::euclNorm)
        .def("clear", &IColumnVector::clear)
        .def("normalize", &IColumnVector::normalize)
        .def("dimension", &IColumnVector::dimension)
        .def("next", &IColumnVector::next)
        // .def("__iter__", [](const IColumnVector &cv) {
        //     return py::make_iterator(cv.begin(), cv.end());
        // }, py::keep_alive<0, 1>())
        .def("assertEqualSize", &IColumnVector::assertEqualSize)
        .def("__repr__",
            [](const IColumnVector &cv) {
                std::ostringstream oss;
                oss << cv;
                return oss.str();
            })
        .def(IVector() + py::self)
        .def(py::self + IVector())
        .def(py::self + py::self)
        .def(IVector() - py::self)
        .def(py::self - IVector())
        .def(py::self - py::self)
        .def("__matmul__", [](const IVector &v1, const IColumnVector &v2) { return v1*v2; })
        .def("__matmul__", [](const IColumnVector &v1, const IVector &v2) { return v1*v2; })
        .def("__matmul__", [](const IColumnVector &v1, const IColumnVector &v2) { return v1*v2; })
        .def(-py::self)
        .def(ScalarType() * py::self)
        .def(py::self * ScalarType())
        .def(py::self / ScalarType())
        .def(py::self *= ScalarType())
        .def(py::self /= ScalarType())
        ;
}