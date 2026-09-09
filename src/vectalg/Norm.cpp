#include <capd/vectalg/Norm.h>

template<typename NormBase = capd::vectalg::Norm<
    capd::vectalg::Vector<capd::interval, CAPD_DEFAULT_DIMENSION>,
    capd::vectalg::Matrix<capd::interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>
>>
class PyNorm : public NormBase, public pybind11::trampoline_self_life_support {
public:   
    typedef typename capd::vectalg::Vector<
        capd::interval, CAPD_DEFAULT_DIMENSION> VectorType;
    typedef typename capd::vectalg::Matrix<
        capd::interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION> MatrixType;
    typedef typename NormBase::ScalarType ScalarType;

    using NormBase::NormBase;

    virtual ScalarType operator()(const VectorType &iv) const override {
        PYBIND11_OVERRIDE_PURE_NAME(ScalarType, NormBase, "__call__", operator(), iv);
    }
    virtual ScalarType operator()(const MatrixType &iv) const override {
        PYBIND11_OVERRIDE_PURE_NAME(ScalarType, NormBase, "__call__", operator(), iv);
    }
    virtual std::string show(void) const override {
        PYBIND11_OVERRIDE_PURE(std::string, NormBase, show,);
    }
    virtual capd::vectalg::Norm<VectorType, MatrixType> *clone(void) const override {
        PYBIND11_OVERRIDE_PURE(PYBIND11_TYPE(capd::vectalg::Norm<VectorType, MatrixType>*), NormBase, clone,);
    }
};

template<typename NormImplBase>
class PyNormImpl : public PyNorm<NormImplBase> {
public:    
    typedef typename PyNorm<NormImplBase>::VectorType VectorType;
    typedef typename PyNorm<NormImplBase>::MatrixType MatrixType;
    typedef typename NormImplBase::ScalarType ScalarType;
    typedef typename capd::vectalg::Norm<VectorType, MatrixType> NormBaseType;

    using PyNorm<NormImplBase>::PyNorm;

    virtual ScalarType operator()(const VectorType &iv) const override {
        PYBIND11_OVERRIDE_NAME(ScalarType, NormImplBase, "__call__", operator(), iv);
    }
    virtual ScalarType operator()(const MatrixType &iv) const override {
        PYBIND11_OVERRIDE_NAME(ScalarType, NormImplBase, "__call__", operator(), iv);
    }
    virtual std::string show(void) const override {
        PYBIND11_OVERRIDE(std::string, NormImplBase, show,);
    }
    virtual capd::vectalg::Norm<VectorType, MatrixType> *clone(void) const override {
        PYBIND11_OVERRIDE(PYBIND11_TYPE(capd::vectalg::Norm<VectorType, MatrixType>*), NormImplBase, clone,);
    }
};


void wrapNorm(pybind11::module &mod){
    namespace py = pybind11;
    using namespace capd;
    using namespace capd::vectalg;
    using IMatrix = Matrix<capd::interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>;
    using IVector = Vector<capd::interval, CAPD_DEFAULT_DIMENSION>;
    using ScalarType = IVector::ScalarType;

    py::class_<Norm<IVector, IMatrix>, PyNorm<>, py::smart_holder>(mod, "INorm")
        .def("__call__", py::overload_cast<const IVector&>(&Norm<IVector, IMatrix>::operator(), py::const_))
        .def("__call__", py::overload_cast<const IMatrix&>(&Norm<IVector, IMatrix>::operator(), py::const_))
        .def("show", &Norm<IVector, IMatrix>::show)
        .def("clone", &Norm<IVector, IMatrix>::clone)
        .doc() = "A general abstract norm"
    ;

    py::class_<EuclNorm<IVector, IMatrix>, PyNormImpl<EuclNorm<IVector, IMatrix>>, py::smart_holder>(mod, "IEuclNorm")
        .def(py::init<>())
        .def("__call__", py::overload_cast<const IVector&>(&EuclNorm<IVector, IMatrix>::operator(), py::const_))
        .def("__call__", py::overload_cast<const IMatrix&>(&EuclNorm<IVector, IMatrix>::operator(), py::const_))
        .def("show", &EuclNorm<IVector, IMatrix>::show)
        .def("clone", &EuclNorm<IVector, IMatrix>::clone)
        .doc() = "Euclidean norm"
    ;

    py::class_<MaxNorm<IVector, IMatrix>, PyNormImpl<MaxNorm<IVector, IMatrix>>, py::smart_holder>(mod, "IMaxNorm")
        .def(py::init<>())
        .def("__call__", py::overload_cast<const IVector&>(&MaxNorm<IVector, IMatrix>::operator(), py::const_))
        .def("__call__", py::overload_cast<const IMatrix&>(&MaxNorm<IVector, IMatrix>::operator(), py::const_))
        .def("show", &MaxNorm<IVector, IMatrix>::show)
        .def("clone", &MaxNorm<IVector, IMatrix>::clone)
        .doc() = "l_infty norm (max norm)"
    ;

    py::class_<SumNorm<IVector, IMatrix>, PyNormImpl<SumNorm<IVector, IMatrix>>, py::smart_holder>(mod, "ISumNorm")
        .def(py::init<>())
        .def("__call__", py::overload_cast<const IVector&>(&SumNorm<IVector, IMatrix>::operator(), py::const_))
        .def("__call__", py::overload_cast<const IMatrix&>(&SumNorm<IVector, IMatrix>::operator(), py::const_))
        .def("show", &SumNorm<IVector, IMatrix>::show)
        .def("clone", &SumNorm<IVector, IMatrix>::clone)
        .doc() = "l_1 norm"
    ;

    py::class_<EuclLNorm<IVector, IMatrix>, PyNormImpl<EuclLNorm<IVector, IMatrix>>, py::smart_holder>(mod, "IEuclLNorm")
        .def(py::init<>())
        .def("__call__", py::overload_cast<const IVector&>(&EuclLNorm<IVector, IMatrix>::operator(), py::const_))
        .def("__call__", py::overload_cast<const IMatrix&>(&EuclLNorm<IVector, IMatrix>::operator(), py::const_))
        .def("show", &EuclLNorm<IVector, IMatrix>::show)
        .def("clone", &EuclLNorm<IVector, IMatrix>::clone)
        .doc() = "Euclidean Logarithmic Norm"
    ;

    py::class_<MaxLNorm<IVector, IMatrix>, PyNormImpl<MaxLNorm<IVector, IMatrix>>, py::smart_holder>(mod, "IMaxLNorm")
        .def(py::init<>())
        .def("__call__", py::overload_cast<const IVector&>(&MaxLNorm<IVector, IMatrix>::operator(), py::const_))
        .def("__call__", py::overload_cast<const IMatrix&>(&MaxLNorm<IVector, IMatrix>::operator(), py::const_))
        .def("show", &MaxLNorm<IVector, IMatrix>::show)
        .def("clone", &MaxLNorm<IVector, IMatrix>::clone)
        .doc() = "l_infty Logarithmic Norm"
    ;

    py::class_<SumLNorm<IVector, IMatrix>, PyNormImpl<SumLNorm<IVector, IMatrix>>, py::smart_holder>(mod, "ISumLNorm")
        .def(py::init<>())
        .def("__call__", py::overload_cast<const IVector&>(&SumLNorm<IVector, IMatrix>::operator(), py::const_))
        .def("__call__", py::overload_cast<const IMatrix&>(&SumLNorm<IVector, IMatrix>::operator(), py::const_))
        .def("show", &SumLNorm<IVector, IMatrix>::show)
        .def("clone", &SumLNorm<IVector, IMatrix>::clone)
        .doc() = "l_1 Logarithmic norm"
    ;
}