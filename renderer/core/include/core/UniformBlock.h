#pragma once

#include <core/Max.h>
#include <core/Precompiled.h>

namespace blitz
{
    struct UniformBlockField
    {
        UniformBlockField(const char* name, const DataType& type, const size_t off);        
        
        blitz::string fieldName;
        DataType dataType;
        size_t offset;
    };

    struct UniformBlock
    {
        UniformBlock(const uint16& idx, const int8& binding, const char* name, Array<UniformBlockField>* field);

        uint16 index;
        int8 bindingPoint; //-1 if not explicitly specified
        blitz::string blockName;
        Array<UniformBlockField>* blockFields;
    };
} // namespace blitz