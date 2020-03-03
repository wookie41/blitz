#include <core/UniformBlock.h>

namespace blitz
{
    UniformBlockField::UniformBlockField(const char* name, const DataType& type, const size_t off)
    : fieldName(name), dataType(type), offset(off)
    {
    }

    UniformBlock::UniformBlock(const uint16& idx, const int8& binding, const char* name, Array<UniformBlockField>* field)
    : index(idx), bindingPoint(binding), blockName(name), blockFields(fields)
    {
    }
} // namespace blitz