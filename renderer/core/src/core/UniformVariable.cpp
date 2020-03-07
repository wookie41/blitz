#include <core/UniformVariable.h>

namespace blitz
{
    IUniformVariable::IUniformVariable(const blitz::string& name) : variableName(name) {}

    const blitz::string* const IUniformVariable::getName() const { return &variableName; }
} // namespace blitz