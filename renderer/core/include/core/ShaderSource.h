#pragma once

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