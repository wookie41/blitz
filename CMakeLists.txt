cmake_minimum_required(VERSION 3.12)
project(blitz)

set(CMAKE_CXX_STANDARD 17)

#Adding mathfu 3d math library dependency
set(mathfu_build_benchmarks OFF CACHE BOOL "")
set(mathfu_build_tests OFF CACHE BOOL "")

#Finding SDL2 and turning it into a target
find_package(SDL2 REQUIRED)
add_library(sdl2 SHARED IMPORTED)

add_subdirectory(blitzcommon)
add_subdirectory(renderer/core)
add_subdirectory(vendor/mathfu)

add_subdirectory(runner)