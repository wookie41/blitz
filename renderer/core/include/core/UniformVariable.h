#pragma once

#include <core/Precompiled.h>

namespace blitz
{
    class IUniformVariable : public NonCopyable
    {
      public:
        virtual void bind() = 0;
        virtual DataType getType() const = 0;

        hash getNameHash() const;
        const char* const getName() const;

        void setWatcher(void (*newWatcher)(const hash& h));

        virtual bool isDirty() const = 0;

        virtual ~IUniformVariable() = default;

      protected:
        explicit IUniformVariable(const char* const name);

        const hash nameHash;

        //TODO noone is deallocating it right now, but that's okay 
        //since a string pool is going to be introduced for stuff like that
        const char* const variableName;
    };

    template <typename T>
    class UniformVariable : public IUniformVariable
    {
      public:
        UniformVariable(T value, const char* const);
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
    UniformVariable<T>::UniformVariable(T value, const char* const name) : IUniformVariable(name), value(value)
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