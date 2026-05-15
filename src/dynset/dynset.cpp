#include <capd/dynset/lib.h>

void wrapDynset(pybind11::module& mod) {
    namespace py = pybind11;
    using namespace capd;
    using MatrixType = capd::IMatrix;
    using size_type = MatrixType::size_type;
    using ScalarType = MatrixType::ScalarType;
    using VectorType = MatrixType::RowVectorType;
    using AffineSet = geomset::AffineSet<MatrixType>;
    using DoubletonSet = geomset::DoubletonSet<MatrixType>;
    using CenteredDoubletonSet = geomset::CenteredDoubletonSet<MatrixType>;
    using MatrixDoubletonSet = geomset::MatrixDoubletonSet<MatrixType>;
    using MatrixAffineSet = geomset::MatrixAffineSet<MatrixType>;
    using C11DoubletonSet = dynset::C1DoubletonSet<MatrixType, 
        dynset::FactorReorganization<dynset::FullQRWithPivoting<>>>;
    using TimeRangeType = diffAlgebra::TimeRange<ScalarType>;

    py::class_<AffineSet>(mod, "AffineSet")
        .def("get_x", &AffineSet::get_x)
        .def("getElement_x", &AffineSet::getElement_x)
        .def("set_x", &AffineSet::set_x)
        .def("setElement_x", &AffineSet::setElement_x)
        .def("get_r", &AffineSet::get_r)
        .def("getElement_r", &AffineSet::getElement_r)
        .def("set_r", &AffineSet::set_r)
        .def("setElement_r", &AffineSet::setElement_r)
        .def("get_B", &AffineSet::get_B)
        .def("get_invB", &AffineSet::get_invB)
        .def("setToIdentity", &AffineSet::setToIdentity)
        .def("getElement_B", &AffineSet::getElement_B)
        .def("getRow_B", &AffineSet::getRow_B)
        .def("getColumn_B", &AffineSet::getColumn_B)
        .def("set_B", &AffineSet::set_B)
        .def("set_invB", &AffineSet::set_invB)
        .def("setElement_B", &AffineSet::setElement_B)
        .def("setRow_B", &AffineSet::setRow_B<VectorType>)
        .def("setColumn_B", &AffineSet::setColumn_B<VectorType>)
        ;
    
    py::class_<DoubletonSet, AffineSet>(mod, "DoubletonSet")
        .def("affineTransformation", &DoubletonSet::affineTransformation,
            "This method computes value of an affine map f at interval vector represented by this set. "
            "This set is represented as tripleton X=x+C*r0+intersection(B*r,Q*q). "
            "Then f(X) = M*(X-x0) can be computed as M*(x-x0) + (M*C)*r0 + intersection( M*B)*r, (M*Q)*q )",
            py::arg("M"), py::arg("x0"))
        .def("get_r0", &DoubletonSet::get_r0)
        .def("getElement_r0", &DoubletonSet::getElement_r0)
        .def("set_r0", &DoubletonSet::set_r0)
        .def("setElement_r0", &DoubletonSet::setElement_r0)
        .def("get_C", &DoubletonSet::get_C)
        .def("getElement_C", &DoubletonSet::getElement_C)
        .def("getRow_C", &DoubletonSet::getRow_C)
        .def("getColumn_C", &DoubletonSet::getColumn_C)
        .def("set_C", &DoubletonSet::set_C)
        .def("setElement_C", &DoubletonSet::setElement_C)
        .def("setRow_C", &DoubletonSet::setRow_C<VectorType>)
        .def("setColumn_C", &DoubletonSet::setColumn_C<VectorType>)
        ;
    
    py::class_<CenteredDoubletonSet, DoubletonSet>(mod, "CenteredDoubletonSet");
    py::class_<C0Set, TimeRangeType>(mod, "C0Set", py::multiple_inheritance());

    py::class_<C0Rect2Set, CenteredDoubletonSet, C0Set>(mod, "C0Rect2Set")
        .def(py::init<const C0Rect2Set::BaseSet&, ScalarType>(),
            py::arg("set"), py::arg("t"))
        .def(py::init<const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("r"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&,
            const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("B"),py::arg("r"),
            py::arg("t")=TypeTraits<ScalarType>::zero())
        ;

    py::class_<geomset::CenteredTripletonSet<MatrixType>, CenteredDoubletonSet>(mod, "CenteredTripletonSet")
        .def("affineTransformation", &geomset::CenteredTripletonSet<MatrixType>::affineTransformation,
            "This method computes value of an affine map f at interval vector represented by this set. "
            "This set is represented as tripleton X=x+C*r0+intersection(B*r,Q*q). "
            "Then f(X) = M*(X-x0) can be computed as M*(x-x0) + (M*C)*r0 + intersection( M*B)*r, (M*Q)*q )",
            py::arg("M"), py::arg("x0"))
            ;

    py::class_<C0TripletonSet, geomset::CenteredTripletonSet<MatrixType>, C0Set>(mod, "C0TripletonSet")
        .def(py::init<const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("r"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&,
            const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("B"),py::arg("r"),
            py::arg("t")=TypeTraits<ScalarType>::zero())
        .def("setToIdentity", &C0TripletonSet::setToIdentity)
        ;

    py::class_<C0HORect2Set, C0Set>(mod, "C0HORect2Set", py::multiple_inheritance())
        .def(py::init<const C0HOTripletonSet::C0BaseSet&>())
        .def(py::init<const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("r"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&,
            const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("B"),py::arg("r"),
            py::arg("t")=TypeTraits<ScalarType>::zero())
        .def("affineTransformation", &C0HORect2Set::affineTransformation,
            py::arg("M"), py::arg("x0"))
        ;

    py::class_<C0HOTripletonSet, C0Set>(mod, "C0HOTripletonSet", py::multiple_inheritance())
        .def(py::init<const C0HOTripletonSet::C0BaseSet&>())
        .def(py::init<const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("r"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&,
            const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("B"),py::arg("r"),
            py::arg("t")=TypeTraits<ScalarType>::zero())
        .def("affineTransformation", &C0HOTripletonSet::affineTransformation,
            py::arg("M"), py::arg("x0"))
        ;

    py::class_<MatrixAffineSet>(mod, "MatrixAffineSet")
        .def("setToIdentity", &MatrixAffineSet::setToIdentity, "sets the set to identity")
        .def("affineMatrixTransformation", &MatrixAffineSet::affineMatrixTransformation,
            "returns image of the set after affine transformation")
        .def("get_D", &MatrixAffineSet::get_D)
        .def("getElement_D", &MatrixAffineSet::getElement_D)
        .def("getRow_D", &MatrixAffineSet::getRow_D)
        .def("getColumn_D", &MatrixAffineSet::getColumn_D)
        .def("set_D", &MatrixAffineSet::set_D)
        .def("setElement_D", &MatrixAffineSet::setElement_D)
        .def("setRow_D", &MatrixAffineSet::setRow_D<VectorType>)
        .def("setColumn_D", &MatrixAffineSet::setColumn_D<VectorType>)
        .def("get_R", &MatrixAffineSet::get_R)
        .def("getElement_R", &MatrixAffineSet::getElement_R)
        .def("getRow_R", &MatrixAffineSet::getRow_R)
        .def("getColumn_R", &MatrixAffineSet::getColumn_R)
        .def("set_R", &MatrixAffineSet::set_R)
        .def("setElement_R", &MatrixAffineSet::setElement_R)
        .def("setRow_R", &MatrixAffineSet::setRow_R<VectorType>)
        .def("setColumn_R", &MatrixAffineSet::setColumn_R<VectorType>)
        .def("get_invBjac", &MatrixAffineSet::get_invBjac)
        .def("get_Bjac", &MatrixAffineSet::get_Bjac)
        .def("getElement_Bjac", &MatrixAffineSet::getElement_Bjac)
        .def("getRow_Bjac", &MatrixAffineSet::getRow_Bjac)
        .def("getColumn_Bjac", &MatrixAffineSet::getColumn_Bjac)
        .def("set_Bjac", &MatrixAffineSet::set_Bjac)
        .def("setElement_Bjac", &MatrixAffineSet::setElement_Bjac)
        .def("setRow_Bjac", &MatrixAffineSet::setRow_Bjac<VectorType>)
        .def("setColumn_Bjac", &MatrixAffineSet::setColumn_Bjac<VectorType>)
        ;
        

    py::class_<MatrixDoubletonSet, MatrixAffineSet>(mod, "MatrixDoubletonSet")
        .def("setToIdentity", &MatrixDoubletonSet::setToIdentity)
        .def("get_R0", &MatrixDoubletonSet::get_R0)
        .def("getElement_R0", &MatrixDoubletonSet::getElement_R0)
        .def("getRow_R0", &MatrixDoubletonSet::getRow_R0)
        .def("getColumn_R0", &MatrixDoubletonSet::getColumn_R0)
        .def("set_R0", &MatrixDoubletonSet::set_R0)
        .def("setElement_R0", &MatrixDoubletonSet::setElement_R0)
        .def("setRow_R0", &MatrixDoubletonSet::setRow_R0<VectorType>)
        .def("setColumn_R0", &MatrixDoubletonSet::setColumn_R0<VectorType>)
        .def("get_Cjac", &MatrixDoubletonSet::get_Cjac)
        .def("getElement_Cjac", &MatrixDoubletonSet::getElement_Cjac)
        .def("getRow_Cjac", &MatrixDoubletonSet::getRow_Cjac)
        .def("getColumn_Cjac", &MatrixDoubletonSet::getColumn_Cjac)
        .def("set_Cjac", &MatrixDoubletonSet::set_Cjac)
        .def("setElement_Cjac", &MatrixDoubletonSet::setElement_Cjac)
        .def("setRow_Cjac", &MatrixDoubletonSet::setRow_Cjac<VectorType>)
        .def("setColumn_Cjac", &MatrixDoubletonSet::setColumn_Cjac<VectorType>)
        ;

    py::class_<C1Set, TimeRangeType>(mod, "C1Set", py::multiple_inheritance());

    py::class_<C1Rect2Set, CenteredDoubletonSet, MatrixDoubletonSet, C1Set>(mod, "C1Rect2Set")
        .def(py::init<const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("r"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&,
            const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("B"),py::arg("r"),
            py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const C1Rect2Set::C0BaseSet&, const C1Rect2Set::C1BaseSet&, ScalarType>(),
            py::arg("c0part"), py::arg("c1part"), py::arg("t")=TypeTraits<ScalarType>::zero())
        ;

    py::class_<C11Rect2Set, C11DoubletonSet>(mod, "C11Rect2Set")
        .def(py::init<const C11Rect2Set::BaseSet&>())
        ;

    py::class_<C1HORect2Set, C1Set, typename C1Rect2Set::C1BaseSet>(mod, "C1HORect2Set")
        .def(py::init<const C1HORect2Set::C0BaseSet&, const C1HORect2Set::C1BaseSet&, ScalarType>(),
            py::arg("c0part"), py::arg("c1part"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("r"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&,
            const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("B"),py::arg("r"),
            py::arg("t")=TypeTraits<ScalarType>::zero())
        .def("affineTransformation", &C1HORect2Set::affineTransformation,
            py::arg("M"), py::arg("x"))
        ;

    py::class_<C2Set, TimeRangeType>(mod, "C2Set", py::multiple_inheritance())
        .def("__getitem__", [](const C2Set& set, std::tuple<size_type, size_type, size_type> idx){
            return set(std::get<0>(idx),std::get<1>(idx),std::get<2>(idx));
        })
        .def("__getitem__", [](const C2Set& set, std::pair<size_type, size_type> idx){
            return set(idx.first,idx.second);
        })
        .def("__getitem__", [](C2Set& set, size_type i){
            return set(i);
        })
        ;

    py::class_<C2Rect2Set, C2Set, CenteredDoubletonSet, MatrixDoubletonSet>(mod, "C2Rect2Set")
        .def(py::init<const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("r"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&,
            const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("B"),py::arg("r"),
            py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const C2Rect2Set::C0BaseSet&, const C2Rect2Set::C1BaseSet&, ScalarType>(),
            py::arg("c0part"), py::arg("c1part"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const C2Rect2Set::C0BaseSet&, const C2Rect2Set::C1BaseSet&,
            const C2Rect2Set::HessianType&, ScalarType>(),
            py::arg("c0part"), py::arg("c1part"), py::arg("hessian"), py::arg("t")=TypeTraits<ScalarType>::zero())
        ;

    py::class_<CnSet, TimeRangeType>(mod, "CnSet", py::multiple_inheritance())
        .def("__getitem__", [](const CnSet& set, std::pair<size_type, vectalg::Multipointer> idx){
            return set(idx.first, idx.second);
        }, "returns a Taylor coefficients corresponding to multipointer, (1/mp!)d^{mp}f_i")
        .def("__getitem__", [](const CnSet& set, std::pair<size_type, vectalg::Multiindex> idx){
            return set(idx.first, idx.second);
        }, "returns a Taylor coefficients corresponding to multiindex, (1/mp!)d^{mp}f_i")
        .def("__getitem__", [](const CnSet& set, const vectalg::Multipointer& mp){
            return set(mp);
        }, "returns vector of Taylor coefficients corresponding to multipointer, i.e. result[i] = (1/mp!)d^{mp}f")
        .def("__getitem__", [](const CnSet& set, std::tuple<size_type, size_type, size_type> idx){
            return set(std::get<0>(idx),std::get<1>(idx),std::get<2>(idx));
        }, "returns Taylor coefficient corresponding to partial derivative d^2f_i/dx_jdx_c")
        .def("__getitem__", [](const CnSet& set, std::pair<size_type, size_type> idx){
            return set(idx.first, idx.second);
        }, "returns df_j/dx_c")
        .def("__getitem__", [](CnSet& set, size_type i){
            return set(i);
        }, "returns actual value of f_i")
        ;

    py::class_<CnRect2Set, CnSet>(mod, "CnRect2Set", py::multiple_inheritance())
        .def(py::init<const VectorType&, CnRect2Set::size_type, ScalarType>(),
            py::arg("x"), py::arg("degree"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const VectorType&, CnRect2Set::size_type, ScalarType>(),
            py::arg("x"), py::arg("r0"), py::arg("degree"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, CnRect2Set::size_type, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("degree"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&, const VectorType&, CnRect2Set::size_type, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("r"), py::arg("degree"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const VectorType&, const MatrixType&, const VectorType&,
            const MatrixType&, const VectorType&, CnRect2Set::size_type, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("B"),py::arg("r"),
            py::arg("degree"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const CnRect2Set::JetType&, ScalarType>(),
            py::arg("x"), py::arg("t")=TypeTraits<ScalarType>::zero())
        .def(py::init<const CnRect2Set::JetType&, const MatrixType&, const VectorType&, ScalarType>(),
            py::arg("x"), py::arg("C"), py::arg("r0"), py::arg("t")=TypeTraits<ScalarType>::zero())
        ;
}