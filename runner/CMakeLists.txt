project(runner)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} blitz::renderer-core)
mathfu_configure_flags(${PROJECT_NAME})
