#pragma once

#include <core/BufferFiller.h>
#include <core/Context.h>

namespace blitz
{
    class SimpleOpenGLBuffer;
    class OpenGLContext;

    class OpenGLBufferFiller : public BufferFiller
    {
        friend class OpenGLContext;

      public:
        void fill(Buffer* buffer, const FillArgs& fillArgs) override;

      private:
        OpenGLBufferFiller(OpenGLContext* glContext);


        void simpleFill(SimpleOpenGLBuffer* buffer, const FillArgs& fillArgs);

        OpenGLContext* glContext;
    };
} // namespace blitz