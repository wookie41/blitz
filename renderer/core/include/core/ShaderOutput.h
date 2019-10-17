#pragma once

#include <core/Max.h>

namespace blitz
{
    struct ShaderOutput
    {
        DataType type;
        char name[MAX_FRAGMENT_OUTPUT_NAME_LENGTH];
    };
} // namespace blitz