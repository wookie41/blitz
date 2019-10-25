#pragma once

#include <blitzcommon/HashUtils.h>
#include <blitzcommon/NonCopyable.h>
#include <core/DataType.h>
#include <functional>

namespace blitz
{
    using UniformVariableWatcher = std::function<void(hash)>;
    const auto noopWatcher = [](hash h) {};

    class IUniformVariable : public NonCopyable
    {
      public:
        virtual void bind() = 0;
        virtual DataType getType() const = 0;

        hash getNameHash() const;
        const std::string& getName() const;

        void setWatcher(const UniformVariableWatcher& newWatcher);

        virtual bool isDirty() const = 0;

        virtual ~IUniformVariable() = default;

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
        UniformVariable(T value, const std::string& name);
        UniformVariable& operator=(const T& newValue);
        T* operator*();

        bool isDirty() const override;

      protected:
        T value;
        bool dirty = false;
    };

    template <typename T>
    UniformVariable<T>& UniformVariable<T>::operator=(const T& newValue)
    {
        value = newValue;
        watcher(nameHash);
        dirty = true;
        return *this;
    }

    template <typename T>
    UniformVariable<T>::UniformVariable(T value, const std::string& name) : IUniformVariable(name), value(value)
    {
    }

    template <typename T>
    T* UniformVariable<T>::operator*()
    {
        return &value;
    }

    template <typename T>
    bool UniformVariable<T>::isDirty() const
    {
        return dirty;
    }
} // namespace blitz