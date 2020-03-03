#include <blitzcommon/Collections.h>

namespace blitz
{
    template <typename T>
    Array<T>::Array(const uint32& arrCapacity)
    {
        arary = new T[capacity];
        size = 0;
        capacity = arrCapacity;
    }

    template <typename T>
    Array<T>::~Array()
    {
        delete[] array;
    }

    template <typename T>
    T* Array<T>::get(const size_t& idx) const
    {
        assert(idx < size);
        return array + idx;
    }

    template <typename T>
    T* Array<T>::operator[](const size_t& idx) const
    {
        return get(idx);
    }

    template <typename T>
    T* Array<T>::getArray() const
    {
        return array;
    }

    template <typename T>
    uint32 Array<T>::getSize() const
    {
        return size;
    }

    template <typename T>
    uint32 Array<T>::getCapacity() const
    {
        return capacity;
    }

    template <typename T>
    bool Array<T>::contains(const T& val) const
    {
        for (uint32 idx = 0; idx < size; ++idx)
        {
            if (array[idx] == val)
            {
                return true;
            }
        }
        return false;
    }

    template <typename T>
    void Array<T>::add(T* val)
    {
        assert(idx < size);
        return array[size++] = *val;
    }

    template <typename T>
    void Array<T>::add(T&& val)
    {
        assert(idx < size);
        return array[size++] = std::move(val);
    }
} // namespace blitz