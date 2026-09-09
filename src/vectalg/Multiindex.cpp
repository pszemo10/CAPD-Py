#include <capd/vectalg/Multiindex.h>

void wrapMultiindex(pybind11::module &mod)
{
    namespace py = pybind11;
    using namespace capd::vectalg;
    using IntContainer = Container<int,0>;

    py::class_<IntContainer>(mod, "IntContainer")
        .def("__iter__", [](const IntContainer& v) {
            return py::make_iterator(v.begin(), v.end());
        }, py::keep_alive<0, 1>())
        .def("__reversed__", [](const IntContainer& v) {
            return py::make_iterator(v.rend(), v.rbegin());
        }, py::keep_alive<0, 1>())
        .def("resize", &IntContainer::resize)
        .def("__getitem__", [](const IntContainer& v, IntContainer::size_type i) {
            return v[i];
        })
        .def("__setitem__", [](IntContainer& v, IntContainer::size_type i, int value) {
            v[i] = value;
        })
        .def("size", &IntContainer::size)
        .def("__len__", &IntContainer::size)
        .def("empty", &IntContainer::empty)
        .def("clear", &IntContainer::clear)
        ;

    using IntVector = Vector<int,0>;

    py::class_<IntVector, IntContainer>(mod, "IntVector")
        .def("dimension", &IntVector::dimension)
        .def("__repr__", [](const IntVector& v) {
            std::ostringstream oss;
            oss << v;
            return oss.str();
        })
        ;

    py::class_<Multipointer, IntVector, IntContainer>(mod, "Multipointer")
        .def(py::init<>())
        .def(py::init<Multipointer::size_type>())
        .def(py::init<const Multiindex&>())
        .def(py::init<const Multipointer&>())
        .def(py::init([](std::vector<int>& l) {
            return Multipointer(l.size(), l.data());
        }))
        .def(py::init<Multipointer::size_type, bool>())
        .def("module", &Multipointer::module, "order of derivative")
        .def("hasNext", &Multipointer::hasNext)
        .def("factorial", &Multipointer::factorial)
        .def("subMultipointer", &Multipointer::subMultipointer)
        .def_static("generateList", &Multipointer::generateList)
        .def("index", py::overload_cast<Multipointer::size_type, Multipointer::size_type>
            (&Multipointer::index, py::const_))
        .def("index", py::overload_cast<Multipointer::size_type, Multipointer::size_type, const Multipointer&>
            (&Multipointer::index, py::const_))
        .doc() = "Multipointer always contains nondecreasing list of indexes of variables. "
                "For partial derivatives they denote variables with respect to which we differentiate. "
                "For example, a Multipointer mp=(0,0,2,3) corresponds to partial derivative "
                ":math:`\frac{\partial^4}{\partial x_0^2 \partial x_2 \partial x_3}`$ "
                "For power series multipointer denotes variables that form monomial. "
                "e.g.Multipointer mp=(0,0,2,3) correspond to monomial x_0^2x_2x_3"
        ;

    mod.def("sumMultipointers", &sumMultipointers);
    mod.def("addIndex", &addIndex, "returns new multipointer which is multiindex mp with index added in correct place");
    mod.def("push_back", &push_back, "appends index to the end of multipointer mp");
    mod.def("hasIndex", &hasIndex, "checks if multipointer contains index");
    mod.def("indexCount", &indexCount, "returns number of occureneces o of index in mp");
    mod.def("removeIndex", &removeIndex);
    mod.def("power", py::overload_cast<
        const Vector<capd::interval, CAPD_DEFAULT_DIMENSION>&,
        const Multipointer&>(&power<Vector<capd::interval, CAPD_DEFAULT_DIMENSION>>),
        "It computes v^m where v is a vector and m is a multiindex");

    py::class_<Multiindex, IntVector, IntContainer>(mod, "Multiindex")
        .def(py::init<>())
        .def(py::init<Multiindex::size_type>())
        .def(py::init<Multiindex::size_type, const Multipointer&>())
        .def(py::init([](std::vector<int>& l) {
            return Multiindex(l.size(), l.data());
        }))
        .def(py::init<Multiindex::size_type, bool>())
        .def(py::init<const Multiindex&>())
        .def("hasNext", py::overload_cast<>(&Multiindex::hasNext))
        .def("module", &Multiindex::module, "returns sum of multiindex coordinates (i.e. degree of monomial)")
        .def("factorial", &Multiindex::factorial, "for multiindex (a,b,..,n) returns a!b!...n!")
        .def("index", &Multiindex::index, "computes index in the array that corresponds to this multiindex")
        .doc() = "For a Multiindex mi, mi[p] is a number of differentiation with respect to i-th variable. "
                "For example, a Multipointer mp=(0,0,2,3) in 5-dimensional space corresponds to "
                "the Multiindex mi=(2,0,1,1,0). "
                "Hence, Multiindex agrees with standard notation and it contains an additional information "
                "about the dimension of the domain of the function. "
                "For polynomial:  Multiindex stores exponents of a given monomial. "
                "e.g. monomial x^2 z^3 of 4 variables (x,y,z,t) has multiindex (2,0,3,0) "
        ;

    mod.def("power", py::overload_cast<
        const Vector<capd::interval, CAPD_DEFAULT_DIMENSION>&,
        const Multiindex&>(&power<Vector<capd::interval, CAPD_DEFAULT_DIMENSION>>));
}