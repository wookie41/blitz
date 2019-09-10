#pragma once

#include "GL/glew.h"
#include "core/ogl/OpenGLBuffer.h"

namespace blitz
{
    class SimpleOpenGLBuffer : public OpenGLBuffer
    {
        friend class OpenGLContext;

      private:
        SimpleOpenGLBuffer(const GLuint& id, const UsageHint& usageHint);
    };
} // namespace blitz