project(runner C CXX)

add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        CMAKE_CXX_STANDARD 17
        LINKER_LANGUAGE CXX)

#I hate MSVS
if (WIN32)
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLEW_INCLUDE_DIRS})
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR})
endif()

if(WITH_DEBUG_TOOLS)
    target_link_libraries(${PROJECT_NAME} loguru)
endif()

mathfu_configure_flags(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} blitz-renderer-core)