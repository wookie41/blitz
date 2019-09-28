#pragma once

namespace blitz
{
    struct ShaderSource
    {
        const char* name;
        const char* vertexShaderSource;
        const char* geometryShaderSource;
        const char* fragmentShaderSource;

        ~ShaderSource();
    };
}