#include "GL/glew.h"
#include "loguru.hpp"

#include <core/RendererErrorCode.h>
#include <core/ogl/OpenGLContext.h>
#include <core/ogl/buffer/OpenGLBufferFiller.h>
#include <core/ogl/buffer/SimpleOpenGLBuffer.h>
#include <core/ogl/framebuffer/OpenGLFramebuffer.h>
#include <core/ogl/shader/OpenGLVertexArray.h>

namespace blitz::ogl
{
    OpenGLContext::OpenGLContext() : Context::Context() { bufferFiller = new OpenGLBufferFiller(this); }

    OpenGLContext::~OpenGLContext() { delete bufferFiller; }

    Buffer* OpenGLContext::createBuffer(const BufferSpec& bufferSpec)
    {
        if (bufferSpec.initialData != nullptr && bufferSpec.size == 0)
        {
            DLOG_F(ERROR, "[OpenGL] Initial data specified, but the size in buffer spec is 0");
            return nullptr;
        }

        GLuint bufferId;
        glGenBuffers(1, &bufferId);

        auto buffer = new SimpleOpenGLBuffer(bufferId, bufferSpec.usageHint, bufferSpec.readable, bufferSpec.writeable);
        if (bufferSpec.size > 0)
        {
            bufferFiller->fill(buffer, { bufferSpec.initialData, 0, bufferSpec.size, false });
        }

        DLOG_F(INFO, "[OpenGL] Buffer with id %d created", bufferId);
        return buffer;
    }

    const BufferFiller* OpenGLContext::getBufferFiller() { return bufferFiller; }

    VertexArray* OpenGLContext::createVertexArray(const uint8& numAttributes)
    {
        GLuint vaoIdx;
        glGenVertexArrays(1, &vaoIdx);
        return new OpenGLVertexArray(numAttributes, vaoIdx, this);
    }

    Framebuffer* OpenGLContext::createFramebuffer(const uint16& numColorAttachments)
    {
        GLuint framebufferID;
        glCreateFramebuffers(1, &framebufferID);
        assert(framebufferID > 0);
        return new OpenGLFramebuffer(framebufferID, numColorAttachments);
    }
} // namespace blitz::ogl