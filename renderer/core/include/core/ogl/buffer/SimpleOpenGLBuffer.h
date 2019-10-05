#pragma once

#include "GL/glew.h"
#include "OpenGLBuffer.h"

namespace blitz
{
    class SimpleOpenGLBuffer : public OpenGLBuffer
    {
        friend class OpenGLContext;

    public:
        bool isIsReadable() const;

        bool isIsWriteable() const;

    private:
        SimpleOpenGLBuffer(const GLuint& id, const UsageHint& usageHint, bool isWriteable, bool isReadable);
        bool isReadable;
        bool isWriteable;
    };
} // namespace blitz