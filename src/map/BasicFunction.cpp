#include <capd/map/BasicFunction.h>

void wrapBasicFunction(pybind11::module &mod) {
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::map;
    using IBasicFunction = BasicFunction<interval>;

    py::class_<IBasicFunction,
        std::unique_ptr<IBasicFunction, py::nodelete>>
    (mod, "IBasicFunction")
        .def("dimension", &IBasicFunction::dimension,
            "returns number of main variables (does not count time and parameters)")
        .def("imageDimension", &IBasicFunction::imageDimension,
            "returns number of functions (dimension of counterdomain)")
        .def("setOrder", &IBasicFunction::setOrder,
            "allocates necessary memory for ODE solver of order 'order'")
        .def("getOrder", &IBasicFunction::getOrder,
            "returns current order of expansion with respect to the time variable")
        .def("setParameter", py::overload_cast<IBasicFunction::size_type, const capd::interval&>
            (&IBasicFunction::setParameter),
            "sets new value of a parameter of index d.")
        .def("setParameter", py::overload_cast<const std::string&, const capd::interval&>
            (&IBasicFunction::setParameter),
            "sets new value of a parameter. If parameter not found there is no effect.")
        .def("setParameters", [](IBasicFunction& self, const std::vector<capd::interval>& values) {
            self.setParameters(values.data(), values.size());
        },
            "simultaneously sets values of many parameters. It is assumed that given vector"
            " contains values of subsequent parameters.")
        .def("getParameter", py::overload_cast<IBasicFunction::size_type>
            (&IBasicFunction::getParameter, py::const_))
        .def("getParameter", py::overload_cast<const std::string&>
            (&IBasicFunction::getParameter, py::const_))
        .def("setCurrentTime", &IBasicFunction::setCurrentTime,
            "sets actual value of variable that represents time in an ODE.")
        .def("getCurrentTime", &IBasicFunction::getCurrentTime,
            "returns actual value of variable that represents time in an ODE")
        .def("differentiateTime", &IBasicFunction::differentiateTime,
            "sets first derivative of time with respect to time equal to 1")
        .def("setMask", [](IBasicFunction& self, std::vector<capd::vectalg::Multiindex> multiindices) {
            self.setMask(multiindices.begin(), multiindices.end());
        })
        .def("addMultiindexToMask", &IBasicFunction::addMultiindexToMask,
            "Adds new multiindex (along with dependencies) to the existing mask.")
        .def("resetMask", &IBasicFunction::resetMask,
            "Resets the mask of derivatives. In consequence, full jet of derivatives will be computed "
            "after call to any method that computes derivative, hessian or jet.")
        .def("getMask", py::overload_cast<IBasicFunction::size_type>
            (&IBasicFunction::getMask, py::const_))
        .def("getMask", py::overload_cast<IBasicFunction::size_type, IBasicFunction::size_type>
            (&IBasicFunction::getMask, py::const_))
        ;
}