#include <capd/vectalg/Container.h>
#include <capd/vectalg/Vector.h>
#include <capd/vectalg/Vector.hpp>
#include <capd/vectalg/Vector_inline.h>
#include <capd/vectalg/Vector_Interval.hpp>

void wrapVector(pybind11::module &mod){
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::vectalg;
    using IVector = Vector<interval, CAPD_DEFAULT_DIMENSION>;
    using ScalarType = IVector::ScalarType;

    py::register_exception<EmptyIntersectionException>(mod, "EmptyIntersectionError");

    py::class_<IVector, IVector::ContainerType>(mod, "IVector")
        .def(py::init<>())
        .def(py::init<IVector::size_type>())
        .def(py::init<const std::string&>())
        .def(py::init(
            [](const std::vector<ScalarType>& data) {
                return IVector(data.begin(), data.end());
            }))
        .def(py::init<IVector::size_type, bool>(), "it does not insert zeros")
        .def(py::self += py::self)
        .def(py::self -= py::self)
        .def(py::self += ScalarType())
        .def(py::self -= ScalarType())
        .def(py::self *= ScalarType())
        .def(py::self /= ScalarType())
        .def("dimension", &IVector::dimension)
        .def("euclNorm", &IVector::euclNorm, "Euclidean norm")
        .def("normalize", &IVector::normalize, "if possible vector is normalized and true is returned. Otherwise false is returned.")
        .def("sorting_permutation", 
            [](IVector &v) {
                typename IVector::rebind<int>::other perm(v.dimension());
                v.sorting_permutation(perm);
                std::vector<int> result(perm.begin(), perm.end());
                return result;
            })
        .def_static("degree", &IVector::degree)
        .def("__repr__",
            [](const IVector &v) {
                std::ostringstream oss;
                oss << v;
                return oss.str();
            })

        // Vector_inline.h
        
        .def("__abs__", &capd::vectalg::abs<ScalarType, CAPD_DEFAULT_DIMENSION>)
        .def(-py::self)
        .def(py::self + py::self)
        .def(py::self - py::self)
        .def("__matmul__", &capd::vectalg::template operator*<ScalarType, 0>)
        .def(py::self + ScalarType())
        .def(py::self - ScalarType())
        .def(py::self * ScalarType())
        .def(py::self / ScalarType())
        .def(py::self < py::self)
        .def(py::self > py::self)
        .def(py::self <= py::self)
        .def(py::self >= py::self)
        .def(py::self == py::self)
        .def(py::self != py::self)
        ;

    // Vector_Interval.hpp

    mod.def("leftVector", &leftVector<IVector>);
    mod.def("rightVector", &rightVector<IVector>);
    mod.def("maxDiam", &maxDiam<IVector>);
    mod.def("intervalBall", &intervalBall<IVector>);
    mod.def("solveAffineInclusion", py::overload_cast<const IVector&, const IVector&, const IVector&>(&solveAffineInclusion<IVector>));
    mod.def("solveAffineInclusionWithDir",
        [&](const IVector& a, const IVector& p, const IVector& c) {
            int dir;
            interval result = solveAffineInclusion(a, p, c, dir);
            return std::make_tuple(result, dir);
        });
    mod.def("intervalHull", py::overload_cast<const IVector&, const IVector&>(&intervalHull<IVector>));
    mod.def("midVector", &midVector<IVector>);
    mod.def("diam", &diam<IVector>);
    mod.def("intersection", &intersection<IVector>);
}