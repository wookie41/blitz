#pragma once

#include "GL/glew.h"
#include "core/Buffer.h"

namespace blitz
{
    class OpenGLBuffer: public Buffer
    {
    public:
        GLuint getId() const;
        virtual ~OpenGLBuffer();
    protected:
        GLuint id;
    private:
        friend class SDL2Device;
        OpenGLBuffer(const GLuint& id, const UsageHint& usageHint);
    };
}