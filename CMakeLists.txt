cmake_minimum_required(VERSION 3.28.3)
project(CAPD-Py LANGUAGES CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_subdirectory(lib/CAPD)

add_subdirectory(lib/pybind11)
pybind11_add_module(capdpy src/capdpy.cpp)

target_link_libraries(capdpy PRIVATE capd filib)


install(TARGETS capdpy
        LIBRARY DESTINATION .)