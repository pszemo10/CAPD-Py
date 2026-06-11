#include <capd/diffAlgebra/Curve.h>
#include <capd/diffAlgebra/C2Curve.h>
#include <capd/diffAlgebra/CnCurve.h>
#include <capd/dynsys/OdeSolver.h>
#include <capd/dynsys/C2OdeSolver.h>
#include <capd/dynsys/CnOdeSolver.h>

#include "TimeMap.cpp"
#include "AbstractSection.cpp"
#include "AffineSection.cpp"
#include "CoordinateSection.cpp"
#include "NonlinearSection.cpp"
#include "BasicPoincareMap.cpp"
#include "PoincareMap.cpp"

void wrapPoincareModule(pybind11::module& mod)
{
    using namespace capd;
    using IMap = map::Map<vectalg::Matrix<interval, CAPD_DEFAULT_DIMENSION, CAPD_DEFAULT_DIMENSION>>;
    using IOdeSolver = dynsys::OdeSolver<IMap>;
    using IC2OdeSolver = dynsys::C2OdeSolver<IMap>;
    using ICnOdeSolver = dynsys::CnOdeSolver<IMap>;

    wrapTimeMap<IOdeSolver>(mod, "ITimeMap");
    wrapTimeMap<IC2OdeSolver>(mod, "IC2TimeMap");
    wrapTimeMap<ICnOdeSolver, false>(mod, "ICnTimeMap");
    wrapAbstractSection(mod);
    wrapAffineSection(mod);
    wrapCoordinateSection(mod);
    wrapNonlinearSection(mod);
    wrapCrossingDirection(mod);
    wrapBasicPoincareMap<IOdeSolver>(mod, "IBasicPoincareMap");
    wrapBasicPoincareMap<IC2OdeSolver>(mod, "IC2BasicPoincareMap");
    wrapBasicPoincareMap<ICnOdeSolver, true>(mod, "ICnBasicPoincareMap");
    wrapPoincareMap<IOdeSolver>(mod, "IPoincareMap");
    wrapPoincareMap<IC2OdeSolver>(mod, "IC2PoincareMap");
    wrapPoincareMap<ICnOdeSolver, false>(mod, "ICnPoincareMap");
}