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

        void bind(const BufferBindingSpec& bindingSpec) override;
        virtual ~OpenGLBuffer();

      protected:
        OpenGLBuffer(const GLuint& id, const UsageHint& usageHint);

        GLuint glBufferID;
    };
} // namespace blitz::ogl