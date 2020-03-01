project(blitz-renderer-front C CXX)

add_library(${PROJECT_NAME} STATIC
    src/front/Camera.cpp
    src/front/Precompiled.cpp
    src/front/RenderingPath.cpp
    src/front/ForwardRenderingPath.cpp
	src/front/ModelRenderer.cpp)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        CMAKE_CXX_STANDARD 17
        LINKER_LANGUAGE CXX)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_override)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

if(WITH_DEBUG_TOOLS)
    target_link_libraries(${PROJECT_NAME} loguru)
endif()

target_link_libraries(${PROJECT_NAME}
    blitz::common
	blitz-renderer-core
)


if (WIN32)
	target_include_directories(${PROJECT_NAME} PRIVATE ${GLEW_INCLUDE_DIRS})
	target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} glew32 opengl32)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} OpenGL GLEW)
endif()



mathfu_configure_flags(${PROJECT_NAME})
