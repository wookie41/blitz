#include "loguru.hpp"
#include "core/ogl/OpenGLBuffer.h"

namespace blitz
{

    OpenGLBuffer::OpenGLBuffer(const GLuint& id, const UsageHint& usageHint) : Buffer(usageHint), id(id) {}

    GLuint OpenGLBuffer::getId() const { return id; }

    OpenGLBuffer::~OpenGLBuffer()
    {
        DLOG_F(INFO, "[OpenGL] Deleting buffer with id %d", id);
        glDeleteBuffers(1, &id);
    }

} // namespace blitz