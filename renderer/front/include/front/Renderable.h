#pragma once

#include <front/Precompiled.h>

namespace blitz
{
    struct RenderCommand;
    
    struct Renderable
    {
        std::vector<RenderCommand*> renderCommands;        
    };
}