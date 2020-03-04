#include <core/ogl/buffer/OpenGLBuffer.h>
#include <core/ogl/framebuffer/OpenGLRenderBufferAttachment.h>

namespace blitz::ogl
{
    OpenGLBuffer::OpenGLBuffer(const GLuint& id, const UsageHint& usageHint) : Buffer(usageHint), glBufferID(id) {}

    GLuint OpenGLBuffer::getId() const { return glBufferID; }

    OpenGLBuffer::~OpenGLBuffer()
    {
        DLOG_F(INFO, "[OpenGL] Deleting buffer with id %d", glBufferID);
        glDeleteBuffers(1, &glBufferID);
    }

    void OpenGLBuffer::bind(const BufferBindingSpec& bindingSpec)
    {
        GLenum glTarget;
        switch (bindingSpec.bindTarget)
        {
        case VERTEX:
            glTarget = GL_ARRAY_BUFFER;
            break;
        case ELEMENT:
            glTarget = GL_ELEMENT_ARRAY_BUFFER;
            break;
        case WRITE:
            glTarget = GL_COPY_WRITE_BUFFER;
            break;
        case UNIFORM_BLOCK:
            glTarget = GL_UNIFORM_BUFFER;
            break;
        }

        if (glTarget = GL_UNIFORM_BUFFER)
        {
            if (bindingSpec.size > 0 || bindingSpec.offset > 0)
            {
                glBindBufferRange(GL_UNIFORM_BUFFER, bindingSpec->index, glBufferID, bindingSpec.size, bindingSpec.offset);
            }
            else
            {
                glBindBufferBase(GL_UNIFORM_BUFFER, bindingSpec->index, glBufferID);
            }

            return;
        }

        glBindBuffer(glTarget, glBufferID);
    }
} // namespace blitz::ogl