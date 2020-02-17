cmake_minimum_required(VERSION 3.12)
project(blitz)

option(WITH_DEBUG_TOOLS "Should build debug tools")

set(CMAKE_CXX_STANDARD 17)
set(WITH_DEBUG_TOOLS 1)


set(CMAKE_THREAD_PREFER_PTHREAD ON)
find_package(Threads REQUIRED)

#Paths for customCmake modules located in custom places
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/Cmake)

#Append custom locations of libs like this
list(APPEND CMAKE_PREFIX_PATH D:/Libs/glew)
add_library(loguru STATIC vendor/loguru/loguru.cpp)

if (WITH_DEBUG_TOOLS)
    target_include_directories(loguru PUBLIC vendor/loguru)
    set_target_properties(loguru PROPERTIES LINKER_LANGUAGE CXX)

    add_compile_definitions(USE_LIBC_MALLOC)

    if (UNIX)
        target_link_libraries(loguru ${CMAKE_THREAD_LIBS_INIT})
        target_link_libraries(loguru dl)
    endif()
endif()

add_library(testkit INTERFACE)
target_include_directories(testkit INTERFACE vendor/catch/include vendor/fakeit/include)

add_library(stbimage INTERFACE)
target_include_directories(stbimage INTERFACE vendor/stb_image/include)

#Adding mathfu 3d math library dependency
set(mathfu_build_benchmarks OFF CACHE BOOL "")
set(mathfu_build_tests OFF CACHE BOOL "")

if (WIN32)
    link_directories(D:/Libs/SDL2/lib/x64 D:/Libs/glew/lib/Release/x64)
endif()

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_subdirectory(vendor/mathfu)
add_subdirectory(vendor/assimp)

add_subdirectory(memory)

add_subdirectory(blitzcommon)
add_subdirectory(renderer/core)
add_subdirectory(renderer/front)

add_subdirectory(resources)
add_subdirectory(runner)
add_subdirectory(platform)
