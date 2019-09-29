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

        void bindIndexed(const IndexedBindTarget& bindTarget, uint16_t index) override;
        void bindIndexedRange(const IndexedBindTarget& bindTarget, uint16_t index, const Range& range) override;

        ~OpenGLBuffer() override;

      protected:
        OpenGLBuffer(const GLuint& id, const UsageHint& usageHint);

        GLuint glBufferID;
    };
} // namespace blitz