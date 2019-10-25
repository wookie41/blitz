#include "core/ogl/buffer/SimpleOpenGLBuffer.h"

namespace blitz::ogl
{
    SimpleOpenGLBuffer::SimpleOpenGLBuffer(const GLuint& id, const UsageHint& usageHint, bool isReadable, bool isWriteable)
    : OpenGLBuffer(id, usageHint), isReadable(isReadable), isWriteable(isWriteable)
    {
    }

    bool SimpleOpenGLBuffer::isIsReadable() const { return isReadable; }

    bool SimpleOpenGLBuffer::isIsWriteable() const { return isWriteable; }
} // namespace blitz::ogl
