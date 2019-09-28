#pragma once

#include <blitzcommon/HashUtils.h>
#include <functional>

namespace blitz
{

    enum class UniformVariableType
    {
        INTEGER
    };

    using UniformVariableWatcher = std::function<void(hash)>;

    class IUniformVariable
    {
      public:
        virtual void bind() = 0;

        virtual const hash& getNameHash() const = 0;

        virtual const std::string& getName() const = 0;

        virtual UniformVariableType& getType() const = 0;
    };

    template <typename T>
    class UniformVariable : IUniformVariable
    {
      public:
        UniformVariable(const T& value, const std::string& name, UniformVariableWatcher watcher);

        UniformVariable& operator=(const T& newValue);

        const hash& getNameHash() const override;

        const std::string& getName() const override;

      protected:
        T value;
        hash nameHash;
        const std::string& name;
        UniformVariableWatcher watcher;
    };

    template <typename T>
    UniformVariable<T>& UniformVariable<T>::operator=(const T& newValue)
    {
        value = newValue;
        watcher();
        return this;
    }

    template <typename T>
    const std::string& UniformVariable<T>::getName() const
    {
        return name;
    }

    template <typename T>
    const hash& UniformVariable<T>::getNameHash() const
    {
        return nameHash;
    }

    template <typename T>
    UniformVariable<T>::UniformVariable(const T& value, const std::string& name, UniformVariableWatcher watcher)
    : value(value), name(name), nameHash(hashString(name)), watcher(watcher)
    {
    }

} // namespace blitz