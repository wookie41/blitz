#pragma once

#include <string>

namespace blitz
{
    struct ShaderSource
    {
        const char* const name;
        const char* vertexShaderSource;
        const char* geometryShaderSource;
        const char* fragmentShaderSource;
    };
}