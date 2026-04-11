
#include <capd/map/Map.h>
#include <capd/diffAlgebra/BasicCurve.h>
#include <capd/diffAlgebra/BasicC2Curve.h>
#include <capd/diffAlgebra/BasicCnCurve.h>

#include "Hessian.cpp"
#include "CnContainer.cpp"
#include "Jet.cpp"
#include "ParametricCurve.cpp"
#include "BasicCurve.cpp"
#include "Curve.cpp"
#include "BasicC2Curve.cpp"
#include "BasicCnCurve.cpp"
#include "C2Curve.cpp"
#include "CnCurve.cpp"

void wrapDiffAlgebra(pybind11::module_& mod){
    using namespace capd;
    using namespace capd::diffAlgebra;
    using IMap = map::Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using IBasicCurve = BasicCurve<IMap::MatrixType>;
    using IBasicC2Curve = BasicC2Curve<IMap::MatrixType>;
    using IBasicCnCurve = BasicCnCurve<IMap::MatrixType>;

    wrapHessian(mod);
    wrapCnContainer(mod);
    wrapJet(mod);
    wrapParametricCurve<IBasicCurve::MatrixType>(mod, "IParametricCurve");
    wrapParametricCurve<IBasicC2Curve::MatrixType>(mod, "IParametricCurve_C2");
    wrapParametricCurve<IBasicCnCurve::MatrixType>(mod, "IParametricCurve_Cn");
    wrapBasicCurve(mod);
    wrapCurve<IBasicCurve>(mod, "IBasicCurve");
    wrapCurve<IBasicC2Curve>(mod, "IBasicCurve_C2");
    wrapCurve<IBasicCnCurve>(mod, "IBasicCurve_Cn");
    wrapBasicC2Curve(mod);
    wrapBasicCnCurve(mod);
    wrapC2Curve(mod);
    wrapCnCurve(mod);
}