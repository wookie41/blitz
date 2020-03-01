cmake_minimum_required(VERSION 3.12)
project (common)

add_library(${PROJECT_NAME} STATIC 
        src/HashUtils.cpp 
        src/PlatformUtils.cpp
        src/StringUtils.cpp
        src/Collections.cpp)

add_library(blitz::common ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

mathfu_configure_flags(${PROJECT_NAME})