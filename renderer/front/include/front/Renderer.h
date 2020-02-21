#pragma once

#include <front/Precompiled.h>

namespace blitz
{
    struct RenderCommand;
    
    namespace front
    {
        struct Renderable;

        class Renderer : public NonCopyable
        {
          public:
            Renderer() = default;

            virtual Renderable* render() = 0;

            virtual ~Renderer() = default;
        };
    } // namespace front
} // namespace blitz