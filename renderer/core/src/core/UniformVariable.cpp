#include <core/UniformVariable.h>

namespace blitz
{
    IUniformVariable::IUniformVariable(const std::string& name)
    : name(name), nameHash(hashString(name)), watcher(noopWatcher)
    {
    }

    hash IUniformVariable::getNameHash() const { return nameHash; }

    const std::string& IUniformVariable::getName() const { return name; }

    void IUniformVariable::setWatcher(const UniformVariableWatcher& newWatcher)
    {
        IUniformVariable::watcher = newWatcher;
    }
} // namespace blitz