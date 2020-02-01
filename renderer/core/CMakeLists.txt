project(blitz-renderer-core C CXX)

add_library(${PROJECT_NAME} STATIC
        src/core/Precompiled.cpp
        src/core/Globals.cpp
        src/core/Logger.cpp
        src/core/Buffer.cpp
        src/core/Window.cpp
        src/core/Context.cpp
        src/core/VertexArray.cpp
        src/core/Shader.cpp
        src/core/sdl2/SDL2Device.cpp
        src/core/sdl2/SDL2Window.cpp
        src/core/sdl2/SDL2Context.cpp
        src/core/ogl/OpenGLContext.cpp
        src/core/ogl/buffer/OpenGLBuffer.cpp
        src/core/ogl/buffer/SimpleOpenGLBuffer.cpp
        src/core/ogl/buffer/OpenGLBufferFiller.cpp
        src/core/ogl/shader/OpenGLVertexArray.cpp
        src/core/ogl/shader/OpenGLShader.cpp
        src/core/UniformVariable.cpp
        src/core/ogl/uniforms/OpenGLBoolUniformVariable.cpp
        src/core/ogl/uniforms/OpenGLIntegerUniformVariable.cpp
        src/core/ogl/uniforms/OpenGLFloatUniformVariable.cpp
        src/core/ogl/uniforms/OpenGLDoubleUniformVariable.cpp
        src/core/ogl/uniforms/OpenGLVec3UniformVariable.cpp
        src/core/ogl/uniforms/OpenGLVec4UniformVariable.cpp
        src/core/ogl/uniforms/OpenGLMat3UniformVariable.cpp
        src/core/ogl/uniforms/OpenGLMat4UniformVariable.cpp
        src/core/ogl/uniforms/OpenGLSamplerUniformVariable.cpp
        src/core/ogl/shader/OpenGLShaderFactory.cpp
        src/core/ogl/shader/OpenGLShaderCompiler.cpp
        src/core/ogl/shader/OpenGLShaderInspector.cpp
        src/core/ogl/OpenGLDevice.cpp
        src/core/ogl/OpenGLDataType.cpp
        src/core/TextureSampler.cpp
        src/core/Texture.cpp
        src/core/ogl/texture/OpenGLTexture.cpp
        src/core/ogl/texture/OpenGLTextureCreator.cpp
        src/core/ogl/texture/OpenGLSyncReadTexture.cpp
        src/core/ogl/texture/OpenGLTextureUtils.cpp
        src/core/ogl/texture/OpenGLSyncWriteTexture.cpp
        src/core/ogl/texture/OpenGLSyncReadWriteTexture.cpp
        src/core/ogl/texture/OpenGLTextureSampler.cpp
        src/core/ogl/uniforms/OpenGLUniformVariable.cpp
        src/core/Framebuffer.cpp
        src/core/ogl/framebuffer/OpenGLTextureAttachment.cpp
        src/core/ogl/framebuffer/OpenGLFramebuffer.cpp
        src/core/ogl/framebuffer/OpenGLRenderBufferAttachment.cpp
        src/core/RenderPass.cpp
        src/core/BasicRenderer.cpp
        src/core/BasicRenderPass.cpp 
        src/core/ogl/BasicOpenGLRenderer.cpp)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        CMAKE_CXX_STANDARD 17
        LINKER_LANGUAGE CXX)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_override)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

if(WITH_DEBUG_TOOLS)
    target_link_libraries(${PROJECT_NAME} loguru)
endif()

target_link_libraries(${PROJECT_NAME} blitz::common blitz::memory)

if (WIN32)
	target_include_directories(${PROJECT_NAME} PRIVATE ${GLEW_INCLUDE_DIRS})
	target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} SDL2 glew32 opengl32)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} SDL2 OpenGL GLEW)
endif()

mathfu_configure_flags(${PROJECT_NAME})

##add_executable(blitz-renderer-core-tests) #TODO
#target_link_libraries(blitz-renderer-core-tests blitz-renderer-core)
#add_test(blitz-renderer-core-tests blitz-renderer-core-tests)