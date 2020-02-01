#pragma once

#include <core/Precompiled.h>
#include <core/Max.h>

namespace blitz
{
    struct UniformBlockField
    {
        char name[MAX_UNIFORM_BLOCK_FIELD_NAME_LENGTH];
        DataType dataType;
        std::size_t offset;
    };

    struct UniformBlock
    {
        std::uint16_t index;
        char name[MAX_UNIFORM_BLOCK_NAME_LENGTH];
        UniformBlockField fields[MAX_NUMBER_OF_FIELDS_IN_UNIFORM];
        std::uint16_t numberOfFields;
    };
}