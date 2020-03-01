#pragma once

#include <front/Precompiled.h>

namespace blitz
{
    struct RenderCommand;

    namespace front
    {
        struct Renderable
        {
            std::vector<RenderCommand*> renderCommands;
        };
    } // namespace front
} // namespace blitz