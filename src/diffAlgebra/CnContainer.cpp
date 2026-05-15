#include <capd/diffAlgebra/CnContainer.h>

void wrapCnContainer(pybind11::module_& mod){
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::diffAlgebra;
    using namespace capd::vectalg;

    using ICnContainer = CnContainer<interval,
        CAPD_DEFAULT_DIMENSION,
        CAPD_DEFAULT_DIMENSION,
        CAPD_DEFAULT_DIMENSION>;
    using ScalarType = ICnContainer::ObjectType;
    using size_type = ICnContainer::size_type;

    py::class_<ICnContainer, Container<ScalarType, CAPD_DEFAULT_DIMENSION>>(mod, "ICnContainer")
        .def(py::init<size_type, size_type, size_type, const ScalarType&>(),
            "creates a container for polynomial of n variables, m components and degree d. "
            "Each element will be set to p.")
        .def(py::init<size_type, size_type, size_type>(),
            "creates a container for polynomial of n variables, m components and degree d. "
            "Default constructor will be used to initialize each element in the container.")
        .def(py::init<const ICnContainer&>())
        .def("imageDimension", &ICnContainer::imageDimension,
            "returns number of polynomials (dimension of counterdomain)")
        .def("dimension", &ICnContainer::dimension,
            "returns number of variables of the polynomial")
        .def("degree", &ICnContainer::degree,
            "returns degree of the polynomial")
        .def("__getitem__", [](const ICnContainer &c, std::pair<size_type,const Multipointer&> index) {
            return c(index.first, index.second);
        }, "selection of coefficient of i-th component that correspond to multipointer mp")
        .def("__setitem__", [](ICnContainer &c,
        std::pair<size_type,const Multipointer&> index, const ScalarType& value) {
            c(index.first, index.second) = value;
        }, "sets the coefficient of i-th component that correspond to multipointer mp")
        .def("__getitem__", [](const ICnContainer &c,
            std::tuple<size_type,const Multipointer&, const Multipointer&> index)
        {
            return c(std::get<0>(index), std::get<1>(index), std::get<2>(index));
        })
        .def("__setitem__", [](ICnContainer &c,
            std::tuple<size_type,const Multipointer&, const Multipointer&> index, const ScalarType& value)
        {
            c(std::get<0>(index), std::get<1>(index), std::get<2>(index)) = value;
        })
        .def("__getitem__", [](const ICnContainer &c, std::pair<size_type,const Multiindex&> index) {
            return c(index.first, index.second);
        }, "selection of coefficient of i-th component that correspond to multiindex mi")
        .def("__setitem__", [](ICnContainer &c, std::pair<size_type,const Multiindex&> index, const ScalarType& value) {
            c(index.first, index.second) = value;
        }, "sets the coefficient of i-th component that correspond to multiindex mi")
        .def("__getitem__", [](const ICnContainer &c, py::tuple& args) {
            std::vector<int> indices;
            for(int i = 1; i < args.size(); ++i) {
                indices.push_back(args[i].cast<int>());
            }
            return c(args[0].cast<int>(), Multipointer(indices.size(), indices.data()));
        })
        .def("__setitem__", [](ICnContainer &c, py::tuple& args, const ScalarType& value) {
            std::vector<int> indices;
            for(int i = 1; i < args.size(); ++i) {
                indices.push_back(args[i].cast<int>());
            }
            c(args[0].cast<int>(), Multipointer(indices.size(), indices.data())) = value;
        })
        .def("first", &ICnContainer::first, "Selection of elements by multipointers."
            "Iterators do not give information about the index of partial derivative."
            "Access by multipointer is significantly slower than by iterator "
            "because the multipointer must be recomputed to the index in array."
            "Iterators and multipointers read coefficients of a homogeneous polynomial in the same order.")
        .def("hasNext", py::overload_cast<Multipointer&>(&ICnContainer::hasNext, py::const_), "see description of the method first.")
        .def("hasNext", py::overload_cast<Multiindex&>(&ICnContainer::hasNext, py::const_), "see description of the method first.")
        // .def(py::self == py::self)
        ;
}