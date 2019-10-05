#include "core/ogl/buffer/SimpleOpenGLBuffer.h"

namespace blitz
{
    SimpleOpenGLBuffer::SimpleOpenGLBuffer(const GLuint& id, const UsageHint& usageHint, bool isWriteable, bool isReadable)
    : OpenGLBuffer(id, usageHint), isWriteable(isWriteable), isReadable(isReadable)
    {
    }

    bool SimpleOpenGLBuffer::isIsReadable() const { return isReadable; }

    bool SimpleOpenGLBuffer::isIsWriteable() const { return isWriteable; }
} // namespace blitz
