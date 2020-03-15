cmake_minimum_required(VERSION 3.12)
project(blitz-servers C CXX)

add_library(${PROJECT_NAME} STATIC
    src/Shapes2D.cpp
    src/VisualServer2D.cpp
)

add_library(blitz::server ALIAS ${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        CMAKE_CXX_STANDARD 17
        LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} blitz-renderer-core blitz-renderer-front blitz-scene blitz::common)

if (WIN32)
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLEW_INCLUDE_DIRS})
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR})
endif()

if(WITH_DEBUG_TOOLS)
    target_link_libraries(${PROJECT_NAME} loguru)
endif()

add_compile_definitions(USE_LIBC_MALLOC)
mathfu_configure_flags(${PROJECT_NAME})