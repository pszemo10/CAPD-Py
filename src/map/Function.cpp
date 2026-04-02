#include <capd/map/Function.h>

void wrapFunction(pybind11::module &mod) {
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::map;
    using IVector = capd::vectalg::Vector<interval, CAPD_DEFAULT_DIMENSION>;
    using IFunction = Function<IVector>;

    py::class_<IFunction, BasicFunction<capd::interval>>(mod, "IFunction")
        .def(py::init<>(), "creates an univariate constant function f(x)=0")
        .def(py::init<const std::string&>(), "parses expression from given string. "
        "Allocates memory for ODE solver of order 'order'")
        .def("__call__", py::overload_cast<const capd::interval&>(&IFunction::operator(), py::const_),
            "evaluates function a(for univariate case)")
        .def("__call__", py::overload_cast<const IVector&>(&IFunction::operator(), py::const_),
            "evaluates function at a given vector.")
        .def("gradient", &IFunction::gradient,
            "returns gradient of the function computed at vector u")
        .def("setParameters", &IFunction::setParameters,
            "simultaneously sets values of many parameters. "
            "It is assumed that given vector contains values of subsequent parameters.")
        ;
}