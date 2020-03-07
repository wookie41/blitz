#pragma once

#include <core/Max.h>
#include <core/Precompiled.h>

namespace blitz
{
    struct BufferRange;

    struct UniformBlockField
    {
        UniformBlockField();
        UniformBlockField(char* name, const DataType& type, const size_t off);

        blitz::string fieldName;
        DataType dataType;
        size_t offset = 0;
    };

    struct UniformBlock
    {
        UniformBlock();
        UniformBlock(const uint16& idx, const int8& binding, char* name, Array<UniformBlockField>* field);

        uint16 index = 0;
        int8 bindingPoint; //-1 if not explicitly specified
        blitz::string blockName;
        Array<UniformBlockField>* blockFields = nullptr;
        BufferRange* associatedBuffer = nullptr;
    };
} // namespace blitz