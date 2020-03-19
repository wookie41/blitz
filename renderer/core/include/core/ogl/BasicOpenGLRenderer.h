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

        //TODO the renderer should remember if the tests
        //are enabled, to reduce the number of GL state changes
        void setStencilTest(const bool& enabled);
        void setDepthTest(const bool& enabled);
        void setBlendTest(const bool& enabled);

    private:
        unsigned int mapToGLType(const PrimitiveType& type);
    };
} // namespace blitz::ogl