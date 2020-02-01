#pragma once

#include <string>

namespace blitz
{
    struct ShaderSource
    {
        const char* const name;
        const char* const vertexShaderSource;
        const char* const geometryShaderSource;
        const char* const fragmentShaderSource;
    };
}