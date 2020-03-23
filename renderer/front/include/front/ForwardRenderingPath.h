#pragma once

#include <front/Precompiled.h>
#include <front/RenderingPath.h>

namespace blitz
{
    class Shader;
} // namespace blitz

namespace blitz::front
{

    class ForwardRenderingPath : public RenderingPath
    {
      public:
        ForwardRenderingPath(Renderer* renderer);
        void render(RenderList* renderList) override;
    };
} // namespace blitz::front