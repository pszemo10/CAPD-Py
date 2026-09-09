#include <capd/vectalg/MatrixContainer.h>

void wrapMatrixContainer(pybind11::module &mod){
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::vectalg;
    using IMatrixContainer = MatrixContainer<capd::interval, 0, 0>;

    py::class_<IMatrixContainer, Container<IMatrixContainer::ScalarType, CAPD_DEFAULT_DIMENSION>>(mod, "IMatrixContainer")
        .def(py::init<>())
        .def(py::init<IMatrixContainer::size_type, IMatrixContainer::size_type>())
        .def(py::init<const IMatrixContainer &>())
        .def(py::init<IMatrixContainer::size_type, IMatrixContainer::size_type, bool>())
        .def(py::init<const IMatrixContainer::Dimension&, bool>())
        .def(py::init<const IMatrixContainer::Dimension&>())
        .def("numberOfRows", &IMatrixContainer::numberOfRows)
        .def("numberOfColumns", &IMatrixContainer::numberOfColumns)
        .def("size", &IMatrixContainer::size)
        .def("dimension", &IMatrixContainer::dimension)
        .def("resize", py::overload_cast<
                IMatrixContainer::size_type,
                IMatrixContainer::size_type>
            (&IMatrixContainer::resize))
        .doc() = "This class inherits from general Container class "
                "and provides constructors and methods specific for two dimensional data"
        ;
}