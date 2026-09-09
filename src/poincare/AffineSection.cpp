#include <capd/poincare/AffineSection.h>

void wrapAffineSection(pybind11::module& mod)
{
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::poincare;
    using IAffineSection = AffineSection<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using VectorType = IAffineSection::VectorType;
    using MatrixType = IAffineSection::MatrixType;

    py::class_<IAffineSection, AbstractSection<MatrixType>>(mod, "IAffineSection")
        .def(py::init<const VectorType&, const VectorType&>())
        .def("__call__", &IAffineSection::operator())
        .def("setNormalVector", &IAffineSection::setNormalVector)
        .def("setOrigin", &IAffineSection::setOrigin)
        .def("getOrigin", &IAffineSection::getOrigin)
        .def("getNormalVector", &IAffineSection::getNormalVector)
        .def("gradient", &IAffineSection::gradient)
        .def("evalAt", &IAffineSection::evalAt)
        .doc() = "This class serves as an affine Poincare section. The section is defined by two vectors"
                " - new origin of coordinate system and normal vector to hyperplane."
        ;
}