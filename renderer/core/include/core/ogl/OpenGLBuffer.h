#pragma once

#include "GL/glew.h"
#include "core/Buffer.h"

namespace blitz
{
    class OpenGLBuffer: public Buffer
    {
    public:
        OpenGLBuffer(const GLuint& id, const UsageHint& usageHint);
        GLuint getId() const;
        virtual ~OpenGLBuffer();
    protected:
        GLuint id;
    };
}