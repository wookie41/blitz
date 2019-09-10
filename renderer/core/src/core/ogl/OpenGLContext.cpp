#include "loguru.hpp"
#include "GL/glew.h"

#include "core/RendererErrorCode.h"
#include "core/ogl/OpenGLBufferFiller.h"
#include "core/ogl/SimpleOpenGLBuffer.h"
#include "core/ogl/OpenGLContext.h"



namespace blitz
{
    OpenGLContext::OpenGLContext() : Context()
    {
        bufferFiller = new OpenGLBufferFiller(this);
    }

    OpenGLContext::~OpenGLContext() { delete (bufferFiller); }

    Buffer* OpenGLContext::createBuffer(BufferSpec bufferSpec)
    {
        if (bufferSpec.multiBuffersCount > 0)
        {
            exit(RendererErrorCode::OPENGL_MULTI_BUFFERING_NO_SUPPORRTED);
        }

        auto selfLock = std::lock_guard(selfMutex);

        GLuint bufferId;
        glGenBuffers(1, &bufferId);

        DLOG_F(INFO, "[OpenGL] Buffer with id %d created", bufferId);
        return new SimpleOpenGLBuffer(bufferId, bufferSpec.usageHint);
    }

    const BufferFiller* OpenGLContext::getBufferFiller() { return bufferFiller; }


} // namespace blitz