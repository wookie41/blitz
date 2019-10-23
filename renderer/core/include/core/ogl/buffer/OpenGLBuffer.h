#pragma once

#include "GL/glew.h"
#include "core/Buffer.h"

namespace blitz::ogl
{
    class OpenGLBuffer : public Buffer
    {
        friend class SDL2Device;

      public:
        GLuint getId() const;

        void bind(const BufferBindTarget& bindTarget) override;

        virtual ~OpenGLBuffer();

      protected:
        OpenGLBuffer(const GLuint& id, const UsageHint& usageHint);

        GLuint glBufferID;
    };
} // namespace blitz::ogl