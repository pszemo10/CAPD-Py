#include "BasicFunction.cpp"
#include "Function.cpp"
#include "Map.cpp"

void wrapMapModule(pybind11::module &mod){
    wrapBasicFunction(mod);
    wrapFunction(mod);
    wrapMap(mod);
}