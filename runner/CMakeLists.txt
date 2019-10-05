project(runner C CXX)

add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        CMAKE_CXX_STANDARD 17
        LINKER_LANGUAGE CXX)

mathfu_configure_flags(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} blitz-renderer-core)