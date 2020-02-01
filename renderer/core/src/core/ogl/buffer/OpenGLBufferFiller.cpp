#include "core/RendererErrorCode.h"
#include "core/ogl/OpenGLContext.h"
#include "core/ogl/buffer/OpenGLBufferFiller.h"
#include "core/ogl/buffer/SimpleOpenGLBuffer.h"

namespace blitz::ogl
{

    OpenGLBufferFiller::OpenGLBufferFiller(OpenGLContext* glContext) : glContext(glContext) {}

    void OpenGLBufferFiller::fill(Buffer* buffer, const FillArgs& fillArgs)
    {
        auto simpleBuffer = dynamic_cast<SimpleOpenGLBuffer*>(buffer);
        if (simpleBuffer != nullptr)
        {
            simpleFill(simpleBuffer, fillArgs);
            return;
        }

        exit(RendererErrorCode::OPENGL_UNSUPPORTED_BUFFER);
    }

    void OpenGLBufferFiller::simpleFill(SimpleOpenGLBuffer* buffer, const FillArgs& fillArgs)
    {
        // TODO currently for the sake of simplicity, partial updates are not supported
        if (fillArgs.offset > 0)
        {
            exit(OPENGL_UNSUPPORTED_BUFFER_OPERATION);
        }

        if (!buffer->isIsWriteable())
        {
            DLOG_F(ERROR, "[OpenGL] Can't fill buffer with id %d - it's not writeable", buffer->getId());
            return;
        }

        DLOG_F(INFO, "[OpenGL] Filling buffer with id %d with %d bytes, starting from address %p", buffer->getId(),
               fillArgs.dataSizeInBytes, fillArgs.data);

        GLenum usageHint;

        switch (buffer->getUsageHint())
        {
        case UsageHint::STREAM:
        case UsageHint::IMMUTABLE:
            usageHint = GL_STREAM_DRAW;
            break;
        case UsageHint::STATIC:
            usageHint = GL_STATIC_DRAW;
            break;
        }

        buffer->bind(BufferBindTarget::WRITE);

        if (fillArgs.shouldInvalidate)
        {
            GLint bufferSize;
            glGetBufferParameteriv(GL_COPY_WRITE_BUFFER, GL_BUFFER_SIZE, &bufferSize);
            DLOG_F(INFO, "[OpenGL] Orhpaning buffer with id %d, size = %d", buffer->getId(), bufferSize);
            glBufferData(GL_COPY_WRITE_BUFFER, buffer->getId(), NULL, usageHint);
        }

        glBufferData(GL_COPY_WRITE_BUFFER, fillArgs.dataSizeInBytes, fillArgs.data, usageHint);
        glBindBuffer(GL_COPY_WRITE_BUFFER, 0);

        buffer->setSize(fillArgs.dataSizeInBytes);
        DLOG_F(INFO, "[OpenGL] Buffer with id %d filled", buffer->getId());

    }
} // namespace blitz::ogl
