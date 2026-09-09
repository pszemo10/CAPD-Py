# CAPD-Py

Python library for computer assisted proofs in dynamical systems

## Requirements

The package can be installed via pip. Minimum version of Python supported is 3.9.

As the package is currently built from source CMake and python3-dev package are also needed.

## Installation
 
 If you have the requirements satisfied run the following command
 ``` 
 pip install --index-url https://test.pypi.org/simple/ --extra-index-url https://pypi.org/simple --no-deps capd==0.4.0 
 ```

## Building from source

Alternatively you can clone and build the library yourself.
Make sure to include submodules when cloning the library. Uae the following command
```
git clone --recurse-submodules
```
Then make the build directory and build the library like so
```
cmake -B build
cmake --build build
```
After that the shared object file with name starting with ```capdpy``` should appear in the build directory.
This is a package which can be imorted into python by writing ```import capdpy```.
