#include "loguru.hpp"
#include "GL/glew.h"

#include <core/RendererErrorCode.h>
#include <core/ogl/buffer/OpenGLBufferFiller.h>
#include <core/ogl/buffer/SimpleOpenGLBuffer.h>
#include <core/ogl/OpenGLContext.h>
#include <core/ogl/shader/OpenGLVertexArray.h>
#include <core/ogl/framebuffer/OpenGLFramebuffer.h>

namespace blitz::ogl
{
    OpenGLContext::OpenGLContext() : Context::Context()
    {
        bufferFiller = new OpenGLBufferFiller(this);
    }

    OpenGLContext::~OpenGLContext() { delete (bufferFiller); }

    Buffer* OpenGLContext::createBuffer(const BufferSpec& bufferSpec)
    {
        if (bufferSpec.initialData != nullptr && bufferSpec.size == 0)
        {
            DLOG_F(ERROR, "[OpenGL] Initial data specified, but the size in buffer spec is 0");
            return nullptr;
        }
        if (bufferSpec.multiBuffersCount > 0)
        {
            DLOG_F(ERROR, "[OpenGL] Multi-buffering not supported");
            return nullptr;
        }

        GLuint bufferId;
        glGenBuffers(1, &bufferId);

        auto buffer = new SimpleOpenGLBuffer(bufferId, bufferSpec.usageHint, bufferSpec.readable, bufferSpec.writeable);
        if (bufferSpec.size > 0)
        {
            bufferFiller->fill(buffer, {bufferSpec.initialData, 0, bufferSpec.size, false});
        }

        DLOG_F(INFO, "[OpenGL] Buffer with id %d created", bufferId);
        return buffer;
    }

    const BufferFiller* OpenGLContext::getBufferFiller() { return bufferFiller; }

    VertexArray *OpenGLContext::createVertexArray()
    {
        GLuint vaoIdx;
        glGenVertexArrays(1, &vaoIdx);
        return new OpenGLVertexArray(vaoIdx, this);
    }

    Framebuffer *OpenGLContext::createFramebuffer()
    {
        GLuint framebufferID;
        glCreateFramebuffers(1, &framebufferID);
        if (framebufferID <= 0)
        {
            DLOG_F(ERROR, "Failed to create GL framebuffer");
            return nullptr;
        }
        return new OpenGLFramebuffer(framebufferID);
    }
} // namespace blitz::ogl