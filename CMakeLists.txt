cmake_minimum_required(VERSION 3.12)
project(blitz)

set(CMAKE_CXX_STANDARD 17)

#Adding mathfu 3d math library dependency
set(mathfu_build_benchmarks OFF CACHE BOOL "")
set(mathfu_build_tests OFF CACHE BOOL "")
add_subdirectory(vendor/mathfu mathfu)

add_executable(blitz main.cpp)

mathfu_configure_flags(blitz)




