project(blitz-renderer-core C CXX)

add_library(${PROJECT_NAME} STATIC
        src/core/Logger.cpp
        src/core/Buffer.cpp
        src/core/Window.cpp
        src/core/Context.cpp
        src/core/VertexArray.cpp
        src/core/Shader.cpp
        src/core/sdl2/SDL2Device.cpp
        src/core/sdl2/SDL2Window.cpp
        src/core/sdl2/SDL2Context.cpp
        src/core/Globals.cpp
        src/core/ogl/OpenGLContext.cpp
        src/core/ogl/OpenGLBuffer.cpp
        src/core/ogl/SimpleOpenGLBuffer.cpp
        src/core/ogl/OpenGLBufferFiller.cpp
        src/core/ogl/OpenGLVertexArray.cpp 
        src/core/ogl/OpenGLShader.cpp
        src/core/ogl/OpenGLIntegerUniformVariable.cpp
        src/core/ogl/OpenGLShaderFactory.cpp
        src/core/ogl/OpenGLShaderCompiler.cpp
        src/core/ogl/OpenGLShaderInspector.cpp
        src/core/ogl/OpenGLDevice.cpp
        src/core/UniformVariable.cpp)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        CMAKE_CXX_STANDARD 17
        LINKER_LANGUAGE CXX)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_override)

target_include_directories(${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        PRIVATE ${PROJECT_SOURCE_DIR}/include/sdl2
)

if(WITH_DEBUG_TOOLS)
    target_link_libraries(${PROJECT_NAME} loguru)
endif()

target_link_libraries(${PROJECT_NAME} blitz::common SDL2 OpenGL GLEW)
mathfu_configure_flags(${PROJECT_NAME})

##add_executable(blitz-renderer-core-tests) #TODO
#target_link_libraries(blitz-renderer-core-tests blitz-renderer-core)
#add_test(blitz-renderer-core-tests blitz-renderer-core-tests)