#pragma once

#include <front/Precompiled.h>


namespace blitz
{
    struct Renderable;
    struct RenderCommand;
    
    namespace front
    {
        class Renderer : public NonCopyable
        {
          public:
            Renderer() = default;

            virtual Renderable* render() = 0;

            virtual ~Renderer() = default;
        };
    } // namespace front
} // namespace blitz