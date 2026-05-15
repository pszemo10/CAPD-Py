
#include <capd/map/Map.h>
#include <capd/diffAlgebra/BasicCurve.h>
#include <capd/diffAlgebra/BasicC2Curve.h>
#include <capd/diffAlgebra/BasicCnCurve.h>
#include <capd/dynsys/OdeSolver.h>
#include <capd/dynsys/C2OdeSolver.h>
#include <capd/dynsys/CnOdeSolver.h>

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
#include "TimeJet.cpp"
#include "SolutionCurve.cpp"

void wrapDiffAlgebra(pybind11::module_& mod){
    using namespace capd;
    using namespace capd::diffAlgebra;
    using IMap = map::Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using IBasicCurve = BasicCurve<IMap::MatrixType>;
    using IBasicC2Curve = BasicC2Curve<IMap::MatrixType>;
    using IBasicCnCurve = BasicCnCurve<IMap::MatrixType>;
    using IOdeSolver = dynsys::OdeSolver<IMap>;
    using IC2OdeSolver = dynsys::C2OdeSolver<IMap>;
    using ICnOdeSolver = dynsys::CnOdeSolver<IMap>;

    wrapHessian(mod);
    wrapCnContainer(mod);
    wrapJet(mod);
    wrapParametricCurve<IBasicCurve::MatrixType>(mod, "IParametricCurve");
    wrapBasicCurve(mod);
    wrapBasicC2Curve(mod);
    wrapBasicCnCurve(mod);
    wrapCurve<IBasicCurve>(mod, "ICurve");
    wrapCurve<IBasicC2Curve>(mod, "ICurve_C2");
    wrapCurve<IBasicCnCurve>(mod, "ICurve_Cn");
    wrapC2Curve(mod);
    wrapCnCurve(mod);
    wrapTimeJet(mod);
    wrapSolutionCurve<IOdeSolver::SolutionCurve>(mod, "IBaseSolutionCurve", "ISolutionCurve");
    wrapSolutionCurve<IC2OdeSolver::SolutionCurve>(mod, "IBaseSolutionCurve_C2", "ISolutionCurve_C2");
    wrapSolutionCurve<ICnOdeSolver::SolutionCurve>(mod, "IBaseSolutionCurve_Cn", "ISolutionCurve_Cn");
}