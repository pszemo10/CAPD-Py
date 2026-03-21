#include <capd/vectalg/Dimension.h>
#include "Container.cpp"
#include "Vector.cpp"

void wrapVectalg(pybind11::module &mod) {
    wrapContainer(mod);
    wrapVector(mod);
}