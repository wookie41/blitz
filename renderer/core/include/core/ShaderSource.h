#pragma once

namespace blitz
{
    struct ShaderSource
    {
        blitz::string name;
        const char* const vertexShaderSource;
        const char* const geometryShaderSource;
        const char* const fragmentShaderSource;
    };
} // namespace blitz