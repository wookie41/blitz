#include <core/UniformBlock.h>
#include <core/BufferRange.h>

namespace blitz
{
    UniformBlockField::UniformBlockField(const blitz::string& name, const DataType& type, const size_t off)
    : fieldName(name), dataType(type), offset(off)
    {
    }

    UniformBlock::UniformBlock(const uint16& idx, const int8& binding, const blitz::string& name, Array<UniformBlockField>* fields)
    : index(idx), bindingPoint(binding), blockName(name), blockFields(fields)
    {
    }
} // namespace blitz