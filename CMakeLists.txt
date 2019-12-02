cmake_minimum_required(VERSION 3.12)
project(blitz)

option(WITH_DEBUG_TOOLS "Should build debug tools")

set(CMAKE_CXX_STANDARD 17)
set(WITH_DEBUG_TOOLS 1)

set(CMAKE_THREAD_PREFER_PTHREAD ON)
find_package(Threads REQUIRED)

if (WITH_DEBUG_TOOLS)
    add_library(loguru STATIC vendor/loguru/loguru.cpp)
    target_include_directories(loguru PUBLIC vendor/loguru)
    set_target_properties(loguru PROPERTIES LINKER_LANGUAGE CXX)

    if (UNIX)
        target_link_libraries(loguru ${CMAKE_THREAD_LIBS_INIT})
        target_link_libraries(loguru dl)
    endif()
endif()

add_library(testkit INTERFACE)
target_include_directories(testkit INTERFACE vendor/catch/include vendor/fakeit/include)


#Adding mathfu 3d math library dependency
set(mathfu_build_benchmarks OFF CACHE BOOL "")
set(mathfu_build_tests OFF CACHE BOOL "")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_subdirectory(vendor/mathfu)
add_subdirectory(blitzcommon)
add_subdirectory(renderer/core)

add_subdirectory(resources)

add_subdirectory(runner)