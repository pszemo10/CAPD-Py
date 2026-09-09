#include <capd/diffAlgebra/Jet.hpp>

void wrapJet(pybind11::module_& mod){
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::diffAlgebra;

    using IJet = Jet<
        vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>,
        CAPD_DEFAULT_DIMENSION>;
    using ScalarType = IJet::ScalarType;
    using size_type = IJet::size_type;

    py::class_<IJet, CnContainer<
                  ScalarType,
                  IJet::MatrixType::ColumnVectorType::csDim,
                  IJet::MatrixType::RowVectorType::csDim,
                  CAPD_DEFAULT_DIMENSION
                >, vectalg::Container<ScalarType, CAPD_DEFAULT_DIMENSION>>(mod, "IJet")
        .def(py::init<>())
        .def(py::init<size_type, size_type>())
        .def(py::init<size_type, size_type, size_type>())
        .def(py::init<const IJet&>())
        .def("__getitem__", py::overload_cast<const vectalg::Multipointer&>(&IJet::operator(), py::const_),
            "this operator returns a vector of partial derivatives, i.e. result[i] = d^{mp}f_i")
        .def("__getitem__", py::overload_cast<const vectalg::Multiindex&>(&IJet::operator(), py::const_),
            "this operator returns a vector of partial derivatives, i.e. result[i] = d^{mp}f_i")
        .def("__call__", py::overload_cast<>(&IJet::operator(), py::const_),
            "this operator returns value of function as a reference")
        .def("setMatrix", &IJet::setMatrix)
        .def("__call__", py::overload_cast<const IJet::VectorType&>(&IJet::operator(), py::const_))
        .def("derivative", &IJet::derivative)
        .def("__call__", py::overload_cast<const IJet::VectorType&, IJet::MatrixType&>
            (&IJet::operator(), py::const_))
        .def("toString", &IJet::toString, "returns string containing derivatives information",
            py::arg("minFun")=0, py::arg("maxFun")=-1, py::arg("firstVariable")=0,
            py::arg("minDegree")=0, py::arg("maxDegree")=-1, py::arg("precision")=-1)
        .def("__repr__", [](const IJet &j) {
            std::ostringstream oss;
            oss << j;
            return oss.str();
        })
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("__add__", &::operator+<IJet::MatrixType, CAPD_DEFAULT_DIMENSION>)
        .def("__sub__", &::operator-<IJet::MatrixType, CAPD_DEFAULT_DIMENSION>)
        .def("__matmul__", &::operator*<IJet::MatrixType, CAPD_DEFAULT_DIMENSION>)
        .doc() = "The class is used to store coefficients of a truncated power series to degree D"
                " f:R^N->R^M "
        ;

    mod.def("substitutionPowerSeries", &substitutionPowerSeries<IJet::MatrixType, CAPD_DEFAULT_DIMENSION>,
        "the function computes substitution of two power series truncated to the same order as 'first' and 'second'"
        "as a result we obtain an expansion of first(second)");
    mod.def("inverseSeriesCloseToIdentity", &inverseSeriesCloseToIdentity<IJet>,
        "This function computes inverse of power series that is close to identity,"
        "i.e. linear part is the Identity matrix.");
    mod.def("inversePowerSeries", &inversePowerSeries<IJet>,
        "This function computes inverse of a general power series."
        "In this procedure we do not specify how to compute inverse of linear part.");

}