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
    T* Array<T>::operator[](int idx) const
    {
        assert(idx < size);
        return array[idx];
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
} // namespace blitz