#include <capd/poincare/NonlinearSection.h>

void wrapNonlinearSection(pybind11::module& mod)
{
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::poincare;
    using INonlinearSection = NonlinearSection<
        vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using VectorType = INonlinearSection::VectorType;
    using MatrixType = INonlinearSection::MatrixType;

    py::class_<INonlinearSection, AbstractSection<MatrixType>, 
        map::Function<MatrixType::RowVectorType>>(mod, "INonlinearSection")
        .def(py::init<const std::string&>())
        .def("__call__", &INonlinearSection::operator())
        .def("gradient", &INonlinearSection::gradient)
        .def("evalAt", &INonlinearSection::evalAt)
        .def("computeDT", py::overload_cast<
            const INonlinearSection::JetType&, const INonlinearSection::JetType&,
            INonlinearSection::JetType&, INonlinearSection::size_type>
            (&INonlinearSection::computeDT, py::const_),
            py::arg("Px"), py::arg("vfOnPx"), py::arg("dT"), py::arg("degree"))
        .doc() = "This class defines a section defined by an arbitrary function"
        ;
}