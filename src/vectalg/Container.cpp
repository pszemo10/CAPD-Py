#include <capd/vectalg/Container.h>

void wrapContainer(pybind11::module &mod){
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::vectalg;
    using IContainer = Container<capd::interval, CAPD_DEFAULT_DIMENSION>;

    py::class_<IContainer>(mod, "IContainer")
        .def(py::init<>())
        .def(py::init<IContainer::size_type>())
        .def(py::init<IContainer::size_type, bool>())
        .def(py::init<const IContainer &>())
        .def("__iter__", [](const IContainer &c) {
            return py::make_iterator(c.begin(), c.end());
        }, py::keep_alive<0, 1>())
        .def("__reversed__", [](const IContainer &c) {
            return py::make_iterator(c.rbegin(), c.rend());
        }, py::keep_alive<0, 1>())
        .def("resize", &IContainer::resize)
        .def("__getitem__",
            [](const IContainer &c, int index) {
                return c[index];
            })
        .def("__setitem__",
            [](IContainer &c, int index, const IContainer::ScalarType &value) {
                c[index] = value;
            })
        .def("__len__", &IContainer::size)
        .def("size", &IContainer::size)
        .def("empty", &IContainer::empty)
        .def("clear", &IContainer::clear)
        .doc() = "This class is used as a container for vectors, matrices and higher order containers"
        ;
}