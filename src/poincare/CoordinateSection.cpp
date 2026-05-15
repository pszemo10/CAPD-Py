#include <capd/poincare/CoordinateSection.h>

void wrapCoordinateSection(pybind11::module& mod)
{
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::poincare;
    using ICoordinateSection = CoordinateSection<
    vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using VectorType = ICoordinateSection::VectorType;
    using MatrixType = ICoordinateSection::MatrixType;
    using ScalarType = ICoordinateSection::ScalarType;
    using JetType = ICoordinateSection::JetType;
    using size_type = ICoordinateSection::size_type;

    py::class_<ICoordinateSection, AbstractSection<MatrixType>>(mod, "ICoordinateSection")
        .def(py::init<size_type, size_type, ScalarType>(),
            "Constructs section { x in R^D | x_i = c } (indices start at 0)",
            py::arg("D"), py::arg("i"), py::arg("c") = TypeTraits<ScalarType>::zero())
        .def("__call__", &ICoordinateSection::operator())
        .def("setDirection", &ICoordinateSection::setDirection)
        .def("setConstant", &ICoordinateSection::setConstant)
        .def("getNormalVector", &ICoordinateSection::getNormalVector)
        .def("gradient", &ICoordinateSection::gradient)
        .def("gradientByVector", &ICoordinateSection::gradientByVector)
        .def("isSpecialSection", &ICoordinateSection::isSpecialSection)
        .def("evalAt", &ICoordinateSection::evalAt)
        .def("computeDT", py::overload_cast<const JetType&, const JetType&, JetType&, size_type>
            (&ICoordinateSection::computeDT, py::const_),
            py::arg("Px"), py::arg("vfOnPx"), py::arg("dT"), py::arg("degree"))
        ;
}