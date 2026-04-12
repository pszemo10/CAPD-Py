#include <capd/vectalg/Dimension.h>
#include <capd/vectalg/Matrix.h>
#include <capd/map/Map.h>
#include <capd/dynsys/StepControl.h>
#include <capd/diffAlgebra/Curve.h>

#include "StepControlInterface.cpp"
#include "BasicOdeSolver.cpp"
#include "BasicC2OdeSolver.cpp"
#include "BasicCnOdeSolver.cpp"
#include "OdeSolver.cpp"
#include "C2OdeSolver.cpp"
#include "CnOdeSolver.cpp"

void wrapDynsys(pybind11::module& mod) {
    using namespace capd;
    using namespace capd::dynsys;
    using IMap = map::Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using ICurve = diffAlgebra::Curve<diffAlgebra::BasicCurve<IMap::MatrixType>>;
    using IC2Curve = diffAlgebra::C2Curve<diffAlgebra::BasicC2Curve<IMap::MatrixType>>;

    wrapStepControlInterface<ILastTermsStepControl>(mod, "StepControlInterfaceILT");
    wrapStepControlInterface<IEncFoundStepControl>(mod, "StepControlInterfaceIEF");
    wrapBasicOdeSolver<ILastTermsStepControl, ICurve>(mod, "IBasicOdeSolver");
    wrapBasicOdeSolver<ILastTermsStepControl, IC2Curve>(mod, "IBasicOdeSolverC2");
    wrapBasicC2OdeSolver(mod);
    wrapBasicCnOdeSolver(mod);
    wrapOdeSolver<ICurve>(mod, "IOdeSolver");
    wrapOdeSolver<IC2Curve>(mod, "IOdeSolverC2");
    wrapC2OdeSolver(mod);
    wrapCnOdeSolver(mod);
}