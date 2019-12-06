cmake_minimum_required(VERSION 3.12)
project (common)

add_library(${PROJECT_NAME} INTERFACE)
add_library(blitz::common ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
        INTERFACE
        ${PROJECT_SOURCE_DIR}/include
)
