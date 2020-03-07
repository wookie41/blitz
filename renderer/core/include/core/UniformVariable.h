#pragma once

#include <core/Precompiled.h>

namespace blitz
{
    class IUniformVariable : public NonCopyable
    {
      public:
        virtual void bind() = 0;
        virtual DataType getType() const = 0;

        const blitz::string* const getName() const;

        virtual bool isDirty() const = 0;

        virtual ~IUniformVariable() = default;

      protected:
        explicit IUniformVariable(const blitz::string& name);

        // TODO noone is deallocating it right now, but that's okay
        // since a string pool is going to be introduced for stuff like that
        blitz::string variableName;
    };

    template <typename T>
    class UniformVariable : public IUniformVariable
    {
      public:
        UniformVariable(T value, const blitz::string& name);
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
        dirty = true;
        return *this;
    }

    template <typename T>
    UniformVariable<T>::UniformVariable(T value, const blitz::string& name) : IUniformVariable(name), value(value)
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