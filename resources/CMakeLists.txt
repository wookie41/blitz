project(blitz-resources C CXX)

add_library(${PROJECT_NAME} STATIC
        src/Precompiled.cpp)

add_library(blitz::resources ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        CMAKE_CXX_STANDARD 17
        LINKER_LANGUAGE CXX)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_override)

target_include_directories(${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
)

if(WITH_DEBUG_TOOLS)
    target_link_libraries(${PROJECT_NAME} loguru)
endif()

target_link_libraries(${PROJECT_NAME} blitz::common)

add_subdirectory(tests)
mathfu_configure_flags(${PROJECT_NAME})
