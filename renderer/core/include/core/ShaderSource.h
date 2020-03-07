#pragma once

namespace blitz
{
    struct ShaderSource
    {
        char* name;
        const char* const vertexShaderSource;
        const char* const geometryShaderSource;
        const char* const fragmentShaderSource;
    };
} // namespace blitz