#pragma once

#include <front/Precompiled.h>


namespace blitz
{
    struct RenderCommand;
    namespace front
    {
        class Renderer : public NonCopyable
        {
          public:
            Renderer() = default;

            virtual std::vector<RenderCommand*> produceCommands() = 0;

            virtual ~Renderer() = default;
        };
    } // namespace front
} // namespace blitz