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

    IUniformVariable& IUniformVariable::operator=(const IUniformVariable& rhs)
    {
        this->name = rhs.name;
        this->nameHash = rhs.nameHash;
        this->watcher = noopWatcher;
        return *this;
    }

    IUniformVariable::IUniformVariable(const IUniformVariable& rhs) : IUniformVariable(rhs.name) {}
} // namespace blitz