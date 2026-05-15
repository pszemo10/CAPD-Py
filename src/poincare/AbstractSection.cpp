#include <capd/poincare/AbstractSection.hpp>

void wrapAbstractSection(pybind11::module& mod)
{
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::poincare;
    using IAbstractSection = AbstractSection<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using VectorType = IAbstractSection::VectorType;
    using MatrixType = IAbstractSection::MatrixType;
    using HessianType = IAbstractSection::HessianType;

    py::class_<IAbstractSection>(mod, "IAbstractSection")
        .def("gradientByVector", &IAbstractSection::gradientByVector)
        .def("isSpecialSection", &IAbstractSection::isSpecialSection,
            "This is very important function. If it returns true, "
            "class PoincareMap delegates computation of value of section(set) to the section. "
            "Otherwise it is assumed that the set has more information "
            "to compute value of section(set) in most optimal way. "
            "This is quite natural as the set knows its own representation. "
            "This function returns true for instance if the PoincareSection is given by x_i=c, "
            "where x_i is i-th coordinate and c is constant.")
        .def("computeDT", &IAbstractSection::computeDT, "computes gradient of return time",
            py::arg("derivativeOfFlow"), py::arg("gradientOnPx"), py::arg("denominator"), py::arg("result"))
        .def("computeDP", py::overload_cast<const VectorType&, const MatrixType&, const VectorType&, VectorType&>
            (&IAbstractSection::computeDP, py::const_),
            "Simultaneous computation of gradient of return time and derivative of Poincare Map dP.",
            py::arg("Px"), py::arg("derivativeOfFlow"), py::arg("fieldOnPx"), py::arg("dT"))
        .def("computeDP", py::overload_cast<const VectorType&, const MatrixType&, const HessianType&,
                const VectorType&, const VectorType&, const MatrixType&, MatrixType&, HessianType&,
                VectorType&, MatrixType&>(&IAbstractSection::computeDP, py::const_),
            "Simultaneous computation of first and second Taylor coefficients of return time and Poincare map.",
            py::arg("Px"), py::arg("derivativeOfFlow"), py::arg("hessianOfFlow"), py::arg("fieldOnPx"),
            py::arg("d2Phidt2"), py::arg("derOfVectorFieldOnPx"), py::arg("DP"), py::arg("D2P"), py::arg("dT"),
            py::arg("d2T"))
        ;
}