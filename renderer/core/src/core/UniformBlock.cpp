#include <core/UniformBlock.h>

namespace blitz
{
    UniformBlockField::UniformBlockField() {}
    UniformBlockField::UniformBlockField(char* name, const DataType& type, const size_t off)
    : fieldName(name), dataType(type), offset(off)
    {
    }

    UniformBlock::UniformBlock() {}
    UniformBlock::UniformBlock(const uint16& idx, const int8& binding, char* name, Array<UniformBlockField>* fields)
    : index(idx), bindingPoint(binding), blockName(name), blockFields(fields)
    {
    }
} // namespace blitz