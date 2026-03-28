#include <capd/vectalg/Dimension.h>
#include "Container.cpp"
#include "Vector.cpp"
#include "MatrixContainer.cpp"
#include "Matrix.cpp"
#include "ColumnVector.cpp"
#include "RowVector.cpp"
#include "Norm.cpp"
#include "Multiindex.cpp"

void wrapVectalg(pybind11::module &mod) {
    wrapContainer(mod);
    wrapVector(mod);
    wrapMatrixContainer(mod);
    wrapMatrix(mod);
    wrapColumnVector(mod);
    wrapRowVector(mod);
    wrapNorm(mod);
    wrapMultiindex(mod);
}