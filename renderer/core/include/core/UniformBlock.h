#pragma once

#include <core/Precompiled.h>
#include <core/Max.h>

namespace blitz
{
    struct BufferRange;
    struct UniformBlockField
    {
        UniformBlockField() = default;
        UniformBlockField(const blitz::string& name, const DataType& type, const size_t off);

        blitz::string fieldName;
        DataType dataType;
        size_t offset = 0;
    };

    struct UniformBlock
    {
        UniformBlock() = default;
        UniformBlock(const uint16& idx, const int8& binding, const blitz::string& name, Array<UniformBlockField>* field);

        uint16 index = 0;
        int8 bindingPoint; //-1 if not explicitly specified
        blitz::string blockName;
        Array<UniformBlockField>* blockFields = nullptr;
        BufferRange* associatedBuffer = nullptr;
    };
} // namespace blitz