cmake_minimum_required(VERSION 3.12)
project(blitz-scene C CXX)

add_library(${PROJECT_NAME} STATIC src/null.cpp)

add_library(blitz::scene ALIAS ${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        CMAKE_CXX_STANDARD 17
        LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} blitz-renderer-core blitz::common)

if(WITH_DEBUG_TOOLS)
    target_link_libraries(${PROJECT_NAME} loguru)
endif()

add_compile_definitions(USE_LIBC_MALLOC)
mathfu_configure_flags(${PROJECT_NAME})
