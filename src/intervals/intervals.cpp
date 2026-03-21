#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <capd/intervals/lib.h>
#include <sstream>

void wrapIntervals(pybind11::module &mod){
    namespace py = pybind11;
    using namespace capd;
    typedef interval::BoundType BoundType;

    py::register_exception<capd::intervals::IntervalError<BoundType>>(mod, "IntervalError");

    py::class_<interval>(mod, "Interval")
        .def(py::init<>())
        .def(py::init<BoundType>())
        .def(py::init<BoundType, BoundType>())
        .def(py::init<std::string const &, std::string const &>())
        .def("leftBound", &interval::leftBound, "returns the left end of the interval")
        .def("rightBound", &interval::rightBound, "returns the right end of the interval")
        .def("inf", &interval::inf, "returns the left end of the interval")
        .def("sup", &interval::sup, "returns the right endof the interval")
        .def("contains", 
            py::overload_cast<const double &>(&interval::template contains<double>, py::const_),
            "checks if interval contains given point X")
        .def("contains",
            static_cast<bool (interval::*)(const interval &) const>(&interval::contains),
            "checks if interval contains given interval iv")
        .def("containsInInterior",
            py::overload_cast<const double &>(&interval::template containsInInterior<double>, py::const_),
            "checks if interval contains in interior given point X")
        .def("containsInInterior",
            static_cast<bool (interval::*)(const interval &) const>(&interval::containsInInterior),
            "checks if interval contains in interior given interval iv")
        .def("subset", &interval::subset, "checks if interval is subset of iv")
        .def("subsetInterior", &interval::subsetInterior, "checks if interval is subset of interior of iv")
        .def("mid", &interval::mid, "returns middle point of interval")
        .def("abs", &interval::abs, "Returns the interval of absolute values of this interval, i.e.")
        .def("split",
            py::overload_cast<interval &, interval &>(&interval::split, py::const_),
            "Splits interval into the form  mid + remainder, where mid - is middle point")
        .def("split",
            [](interval &A_iv, interval &A_rRemainder) {
                BoundType mid;
                A_iv.split(mid, A_rRemainder);
                return mid;
            },
            "Splits interval into the form  mid + remainder, where mid - is middle point")
        .def_static("pi", &interval::pi, "returns pi constant")
        .def_static("euler", &interval::euler, "returns euler constant")
        .def(py::self += py::self)
        .def(py::self -= py::self)
        .def(py::self *= py::self)
        .def(py::self /= py::self)
        .def(py::self == py::self)
        .def(py::self <= py::self)
        .def(py::self >= py::self)
        .def(py::self < py::self)
        .def(py::self > py::self)
        .def(py::self != py::self)
        .def(py::self == BoundType())
        .def(BoundType() == py::self)
        .def(py::self != BoundType())
        .def(BoundType() != py::self)
        .def(py::self > BoundType())
        .def(BoundType() > py::self)
        .def(py::self >= BoundType())
        .def(BoundType() >= py::self)
        .def(py::self < BoundType())
        .def(BoundType() < py::self)
        .def(py::self <= BoundType())
        .def(BoundType() <= py::self)
        .def(-py::self)
        .def(py::self + py::self)
        .def(py::self - py::self)
        .def(py::self * py::self)
        .def(py::self / py::self)
        .def("__pow__", [](const interval &a, int n) { return a ^ n; })
        .def("__pow__", [](const interval &a, unsigned n) { return a ^ n; })
        .def("__pow__", [](const interval &a, BoundType n) { return a ^ n; })
        .def("__pow__", [](const interval &a, const interval &b) { return a ^ b; })
        .def(py::self + BoundType())
        .def(BoundType() + py::self)
        .def(py::self - BoundType())
        .def(BoundType() - py::self)
        .def(py::self * BoundType())
        .def(BoundType() * py::self)
        .def(BoundType() / py::self)
        .def(py::self / BoundType())
        .def("__repr__",
            [](const interval &iv) {
                std::ostringstream oss;
                oss << iv;
                return oss.str();
            })
        ;
        
    mod.def("leftBound", [](const interval &x) { return leftBound(x); }, 
        "returns the left end of the interval");
    mod.def("rightBound", [](const interval &x) { return rightBound(x); }, 
        "returns the right end of the interval");
    mod.def("inf", [](const interval &x) { return inf(x); }, 
        "returns the left end of the interval");
    mod.def("sup", [](const interval &x) { return sup(x); }, 
        "returns the right end of the interval");
    mod.def("left", [](const interval &x) { return left(x); }, 
        "returns interval containing left end");
    mod.def("right", [](const interval &x) { return right(x); }, 
        "returns interval containing right end");
    mod.def("subset", [](const interval &A_iv1, const interval &A_iv2) { return subset(A_iv1, A_iv2); }, 
        "checks if interval is subset of iv");
    mod.def("subsetInterior", [](const interval &A_iv1, const interval &A_iv2) { return subsetInterior(A_iv1, A_iv2); }, 
        "checks if interval is subset of interior of iv");
    mod.def("diam", 
        &capd::filib::template diam<interval::BoundType, 
            ::filib::native_directed, ::filib::i_mode_normal>);
    mod.def("mid", [](const interval &A_iv) { return mid(A_iv); });
    mod.def("intersection", 
        [](const interval &A_iv1, const interval &A_iv2) {
            interval r;
            bool res = intersection(A_iv1, A_iv2, r);
            return res ? std::make_optional(std::optional<interval>(r)) : std::optional<interval>();
        },
        "Intersection of two intervals");
    mod.def("intervalHull",
        [](const interval &ix, const interval &iy) { return intervalHull(ix, iy); },
        "returns an interval containing ix and iy");
    mod.def("split", 
        [](interval &A_iv) {
            interval mid;
            BoundType r;
            split(A_iv, mid, r);
            return std::make_tuple(mid, r);
        },
        "On output:  iv \\subset Mid + [-diam , diam]");
    mod.def("isSingular", [](const interval &A_x) { return isSingular(A_x); });
    mod.def("power", 
        static_cast<interval (*)(const interval &, int)>(
            [](const interval &x, int n) { return power(x, n); })); // which types?
    mod.def("power", 
        static_cast<interval (*)(const interval &, unsigned)>(
            [](const interval &x, unsigned n) { return power(x, n); }));
    mod.def("power", 
        static_cast<interval (*)(const interval &, BoundType)>(
            [](const interval &x, BoundType n) { return power(x, n); }));
    mod.def("power",
        static_cast<interval (*)(const interval &, interval)>(
            [](const interval &a, interval b) { return power(a, b); }));
    mod.def("sqrt", [](const interval &x) { return sqrt(x); });
    mod.def("sin", [](const interval &x) { return sin(x); });
    mod.def("cos", [](const interval &x) { return cos(x); });
    mod.def("tan", [](const interval &x) { return tan(x); });
    mod.def("cot", [](const interval &x) { return cot(x); });
    mod.def("atan", [](const interval &x) { return atan(x); });
    mod.def("atan2", [](const interval &x, const interval &y) { return atan2(x, y); });
    mod.def("asin", [](const interval &x) { return asin(x); });
    mod.def("acos", [](const interval &x) { return acos(x); });
    mod.def("sinh", [](const interval &x) { return sinh(x); });
    mod.def("cosh", [](const interval &x) { return cosh(x); });
    mod.def("tanh", [](const interval &x) { return tanh(x); });
    mod.def("coth", [](const interval &x) { return coth(x); });
    mod.def("exp", [](const interval &x) { return exp(x); });
    mod.def("log", [](const interval &x) { return log(x); });
    mod.def("sqr", [](const interval &x) { return sqr(x); });
    mod.def("isinf", [](const interval &x) { return isinf(x); }, "returns true if any of endpoints is infinite");
    mod.def("isnan", [](const interval &x) { return isnan(x); }, "returns true if any of endpoints is a NaN");
    mod.def("copysign", 
        [](const interval &x, const interval &y) { return copysign(x, y); },
        "returns interval containing copysign(a, b) for each a in x and b in y");
    mod.def("nonnegativePart", 
        [](const interval &x) { return nonnegativePart(x); },
        "returns nonnegative part of interval. if nonnegative part is empty throws exception");
    mod.def("ball", 
        [](const interval &iv, const interval &r) { return ball(iv, r); },
        "Ball with center iv and radius r");
    mod.def("ball", 
        [](const interval &iv, BoundType r) { return ball(iv, r); },
        "Ball with center iv and radius r");
    mod.def("solveAffineInclusion",
        [](const interval &a, const interval &p, const interval &c) {
            return solveAffineInclusion(a, p, c);
        }, "solves inclusion a+[0,t]*p \\subset c for t");
    // mod.def("solveAffineInclusionWithDir",
    //     [](const interval &a, const interval &p, const interval &c, int &dir) {
    //         interval result = solveAffineInclusion(a, p, c, dir);
    //         return std::make_tuple(result, dir);
    //     }, "solves inclusion a+[0,t]*p \\subset c for t");

    py::implicitly_convertible<BoundType, interval>();
}