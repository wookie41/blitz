cmake_minimum_required(VERSION 3.12)
project(blitz-platform-os)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC src/FileSystem.cpp
        src/linux/LinuxFileSystem.cpp)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        CMAKE_CXX_STANDARD 17
        LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} blitz::common)

if(WITH_DEBUG_TOOLS)
    target_link_libraries(${PROJECT_NAME} loguru)
endif()