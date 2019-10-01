#pragma once

#include <string>

namespace blitz
{
    struct ShaderSource
    {
        std::string name;
        const char* vertexShaderSource;
        const char* geometryShaderSource;
        const char* fragmentShaderSource;
    };
}