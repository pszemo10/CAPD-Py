#include <capd/diffAlgebra/Hessian.h>
#include <capd/diffAlgebra/Jet.hpp>

void wrapHessian(pybind11::module_& mod){
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::diffAlgebra;

    using IHessian = Hessian<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>;
    using ScalarType = IHessian::ScalarType;
    using size_type = IHessian::size_type;
    using IMatrix = capd::vectalg::Matrix<ScalarType, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>;

    py::class_<IHessian, vectalg::Container<ScalarType, CAPD_DEFAULT_DIMENSION>>(mod, "IHessian")
        .def(py::init<const IHessian&>())
        .def(py::init<>())
        .def(py::init<size_type>())
        .def(py::init<size_type, size_type>())
        .def(py::init([](size_type image, size_type domain, const std::vector<ScalarType>& data) {
            return IHessian(image, domain, data.data());
        }))
        .def("__getitem__", [](const IHessian &h,
            std::tuple<size_type,size_type,size_type> index) {
                return h(std::get<0>(index), std::get<1>(index), std::get<2>(index));
            })
        .def("__setitem__", [](IHessian &h,
            std::tuple<size_type,size_type,size_type> index,
            const ScalarType& value) {
                h(std::get<0>(index), std::get<1>(index), std::get<2>(index)) = value;
            })
        .def("__getitem__", [](IHessian &h, std::pair<size_type,size_type> index) {
                return h(index.first, index.second);
            })
        .def(py::self += py::self, "component-wise addition")
        .def(py::self *= interval(), "multiplication of each coefficient by a scalar")
        .def("dimension", &IHessian::dimension, "dimension of the phase space")
        .def("imageDimension", &IHessian::imageDimension, "dimension of codomain")
        .def("resize", &IHessian::resize)
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def(IMatrix() * py::self)
        .def(py::self * IMatrix())
        .def(ScalarType() * py::self)
        .def(py::self + py::self)

        // from sets

        .def(py::init([](const typename diffAlgebra::Jet<IMatrix, CAPD_DEFAULT_DIMENSION>& jet) {
            return (IHessian)jet;
        }))
        .def(py::init([](const C2Set& set){
            return (IHessian)set;
        }))
        .doc() = "This class is used to store second order partial derivatives of a function R^D\to R^M . "
                "It provides indexing, iterators and some algorithms for hessians."
        ;
}