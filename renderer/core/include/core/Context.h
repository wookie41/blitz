#pragma once

#include <core/Buffer.h>
#include <core/Precompiled.h>

namespace blitz
{
    class BufferFiller;
    class VertexArray;
    class Framebuffer;

    class Context : private NonCopyable
    {
      public:
        virtual Buffer* createBuffer(const BufferSpec& bufferSpec) = 0;
        virtual VertexArray* createVertexArray(const uint8& numAttributes) = 0;
        virtual Framebuffer* createFramebuffer(const uint16& numColorAttachments) = 0;
        virtual const BufferFiller* getBufferFiller() = 0;

        virtual ~Context() = default;
    };
} // namespace blitz