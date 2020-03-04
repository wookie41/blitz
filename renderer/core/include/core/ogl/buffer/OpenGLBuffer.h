#pragma once

#include <core/Buffer.h>
#include <core/Precompiled.h>

namespace blitz::ogl
{
    class OpenGLBuffer : public Buffer
    {
        friend class SDL2Device;

      public:
        GLuint getId() const;

        virtual void bind(const BufferBindingSpec& bindingSpec) = 0;
        virtual ~OpenGLBuffer();

      protected:
        OpenGLBuffer(const GLuint& id, const UsageHint& usageHint);

        GLuint glBufferID;
    };
} // namespace blitz::ogl