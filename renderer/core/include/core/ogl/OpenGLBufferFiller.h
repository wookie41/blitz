#pragma once

#include <cstdint>
#include <core/Context.h>
#include "core/BufferFiller.h"

namespace blitz
{
    class SimpleOpenGLBuffer;
    class OpenGLContext;

    class OpenGLBufferFiller :public BufferFiller
    {
    public:
        OpenGLBufferFiller(OpenGLContext* glContext);

        void fill(Buffer *buffer, const FillArgs &fillArgs) override;
    private:

        void simpleFill(SimpleOpenGLBuffer* buffer, const FillArgs& fillArgs);

        OpenGLContext* glContext;
    };
}