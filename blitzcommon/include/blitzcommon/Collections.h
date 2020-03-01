#pragma once

#include <blitzcommon/DataType.h>

namespace blitz
{
    template <typename T>
    struct ListNode
    {
        T* node;
        ListNode<T>* next;
    };

    template <typename T>
    struct Array
    {
        explicit Array(const uint32& arrCapacity);
        ~Array();

        T* operator[](int idx) const;
        T* getArray() const;

        uint32 getSize() const;
        uint32 getCapacity() const;

      private:
        T* array;
        uint32 capacity;
        uint32 size;
    };
} // namespace blitz