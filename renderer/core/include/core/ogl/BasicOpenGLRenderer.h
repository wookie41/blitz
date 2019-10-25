#pragma once

#include <core/BasicRenderer.h>

namespace blitz::ogl
{
    class BasicOpenGLRenderer : public BasicRenderer
    {
      public:
        BasicOpenGLRenderer() = default;
        ~BasicOpenGLRenderer() = default;

      protected:
        void run(RenderCommand *renderCommand) override;

        void setViewPort(const ViewPort *viewPort) override;

    private:
        unsigned int mapToGLType(const PrimitiveType& type);
    };
} // namespace blitz::ogl