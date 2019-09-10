#pragma once

#include "GL/glew.h"
#include "core/ogl/OpenGLBuffer.h"

namespace blitz
{
    class SimpleOpenGLBuffer : public OpenGLBuffer
    {
      private:
        friend class OpenGLContext;
        SimpleOpenGLBuffer(const GLuint& id, const UsageHint& usageHint);
    };
} // namespace blitz