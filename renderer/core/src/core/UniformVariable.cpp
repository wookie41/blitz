#include <core/UniformVariable.h>

namespace blitz
{
    IUniformVariable::IUniformVariable(const char* const name)
    : variableName(name), nameHash(hashString(name)), watcher(noopWatcher)
    {
    }

    hash IUniformVariable::getNameHash() const { return nameHash; }

    const char* const IUniformVariable::getName() const { return variableName; }

    void IUniformVariable::setWatcher(const UniformVariableWatcher& newWatcher)
    {
        IUniformVariable::watcher = newWatcher;
    }
} // namespace blitz