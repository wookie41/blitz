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
    const auto noopWatcher = [](hash h) {};

    class IUniformVariable
    {
      public:
        IUniformVariable(const IUniformVariable& rhs);

        virtual void bind() = 0;
        virtual UniformVariableType getType() const = 0;

        hash getNameHash() const;
        const std::string& getName() const;

        void setWatcher(const UniformVariableWatcher& newWatcher);

        IUniformVariable& operator=(const IUniformVariable& rhs);

      protected:
        explicit IUniformVariable(const std::string& name);

        hash nameHash;
        std::string name;
        UniformVariableWatcher watcher;
    };

    template <typename T>
    class UniformVariable : public IUniformVariable
    {
      public:
        UniformVariable(const T& value, const std::string& name);
        UniformVariable& operator=(const T& newValue);

      protected:
        T value;
    };

    template <typename T>
    UniformVariable<T>& UniformVariable<T>::operator=(const T& newValue)
    {
        value = newValue;
        watcher(nameHash);
        return *this;
    }

    template <typename T>
    UniformVariable<T>::UniformVariable(const T& value, const std::string& name) : IUniformVariable(name), value(value)
    {
    }

} // namespace blitz