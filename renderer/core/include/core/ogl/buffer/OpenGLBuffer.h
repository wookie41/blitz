#pragma once

#include "GL/glew.h"
#include "core/Buffer.h"

namespace blitz
{
    class OpenGLBuffer : public Buffer
    {
        friend class SDL2Device;

      public:
        GLuint getId() const;

        void bind(const BindTarget& bindTarget) override;

        ~OpenGLBuffer() override;

      protected:
        OpenGLBuffer(const GLuint& id, const UsageHint& usageHint);

        GLuint glBufferID;
    };
} // namespace blitz