#include <sstream>

#include <capd/diffAlgebra/TimeRange.h>
#include <capd/diffAlgebra/C0TimeJet.h>
#include <capd/diffAlgebra/C1TimeJet.h>
#include <capd/diffAlgebra/C2TimeJet.h>
#include <capd/diffAlgebra/CnTimeJet.h>

void wrapTimeJet(pybind11::module& mod) {
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::diffAlgebra;
    using MatrixType = vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>;
    using MatrixScalarType = MatrixType::ScalarType;
    using ITimeRange = TimeRange<MatrixScalarType>;
    using IC0TimeJet = C0TimeJet<MatrixType::RowVectorType>;
    using IC1TimeJet = C1TimeJet<MatrixType>;
    using IC2TimeJet = C2TimeJet<MatrixType>;
    using ICnTimeJet = CnTimeJet<MatrixType, 0>;

    py::class_<ITimeRange>(mod, "ITimeRange")
        .def(py::init<const ITimeRange::ScalarType&>())
        .def("getCurrentTime", &ITimeRange::getCurrentTime)
        .def("setCurrentTime", &ITimeRange::setCurrentTime)
        .doc() = "TimeRange is a base class for all types of sets. It stores the current time in ODE case "
                "or number of iterations in the case of discrete dynamical system case."
        ;

    py::class_<IC0TimeJet, ITimeRange>(mod, "IC0TimeJet")
        .def(py::init<IC0TimeJet::size_type>())
        .def(py::init([](IC0TimeJet::VectorType& v) {
            return IC0TimeJet(&v);
        }), py::keep_alive<1, 2>())
        .def("clear", &IC0TimeJet::clear)
        .def("vector", py::overload_cast<>(&IC0TimeJet::vector, py::const_))
        .def("setVector", &IC0TimeJet::setVector)
        .def("__repr__", [](const IC0TimeJet& jet) {
            std::ostringstream ss;
            ss << jet;
            return ss.str();
        })
        .def("dimension", &IC0TimeJet::dimension)
        .def_static("degree", &IC0TimeJet::degree)
        ;

    py::class_<IC1TimeJet, IC0TimeJet>(mod, "IC1TimeJet")
        .def(py::init<IC1TimeJet::size_type>())
        .def(py::init([](IC1TimeJet::VectorType& v, IC1TimeJet::MatrixType& m) {
            return IC1TimeJet(&v, &m);
        }), py::keep_alive<1, 2>(), py::keep_alive<1, 3>())
        .def("clear", &IC1TimeJet::clear)
        .def("matrix", py::overload_cast<>(&IC1TimeJet::matrix, py::const_))
        .def("setMatrix", &IC1TimeJet::setMatrix)
        .def("__repr__", [](const IC1TimeJet& jet) {
            std::ostringstream ss;
            ss << jet;
            return ss.str();
        })
        .def_static("degree", &IC1TimeJet::degree)
        ;

    py::class_<IC2TimeJet, IC1TimeJet>(mod, "IC2TimeJet")
        .def(py::init<IC2TimeJet::size_type>())
        .def(py::init([](IC2TimeJet::VectorType& v,
            IC2TimeJet::MatrixType& m,
            IC2TimeJet::HessianType& h)
        {
            return IC2TimeJet(&v, &m, &h);
        }), py::keep_alive<1, 2>(), py::keep_alive<1, 3>(), py::keep_alive<1, 4>())
        .def("clear", &IC2TimeJet::clear)
        .def("setHessian", &IC2TimeJet::setHessian)
        .def("hessian", py::overload_cast<>(&IC2TimeJet::hessian, py::const_))
        .def("__repr__", [](const IC2TimeJet& jet) {
            std::ostringstream ss;
            ss << jet;
            return ss.str();
        })
        .def_static("degree", &IC2TimeJet::degree)
        ;

    py::class_<ICnTimeJet, ITimeRange>(mod, "ICnTimeJet")
        .def(py::init([](ICnTimeJet::JetType& j) {
            return ICnTimeJet(&j);
        }), py::keep_alive<1, 2>())
        .def("vector", py::overload_cast<>(&ICnTimeJet::vector, py::const_))
        .def("degree", &ICnTimeJet::degree)
        .doc() = "This class represents a jet of solution to a nonautomnomous ODE. "
                "This is a truncated power series of degree D of a function "
                " t to R^n"
                "at given time \n\n"
                "The base class Jet is used to store coefficients of the jet. "
                "The base class TimeRange is used to store current time. "
        ;
}