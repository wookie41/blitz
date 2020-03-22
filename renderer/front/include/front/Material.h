#pragma once

#include <front/Precompiled.h>
#include <core/RenderCommand.h>

namespace blitz
{
    class Shader;

    struct Material
    {
        Shader* shader = nullptr;
        Array<UniformState>* properties = nullptr;
    };
} // namespace blitz
