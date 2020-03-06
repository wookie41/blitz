#include <core/UniformVariable.h>

namespace blitz
{
    IUniformVariable::IUniformVariable(const char* const name)
    : variableName(name), nameHash(hashString(name))
    {
    }

    hash IUniformVariable::getNameHash() const { return nameHash; }

    const char* const IUniformVariable::getName() const { return variableName; }
} // namespace blitz