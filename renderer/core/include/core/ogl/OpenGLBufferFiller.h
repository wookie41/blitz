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
        void fill(Buffer *buffer, const FillArgs &fillArgs) override;
    private:
        friend class OpenGLContext;
        OpenGLBufferFiller(OpenGLContext* glContext);


        void simpleFill(SimpleOpenGLBuffer* buffer, const FillArgs& fillArgs);

        OpenGLContext* glContext;
    };
}