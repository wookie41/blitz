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

        T* get(const size_t& idx) const;
        T* operator[](const size_t& idx) const;
        T* getArray() const;

        void add(T* val);
        void add(T&& val);

        uint32 getSize() const;
        uint32 getCapacity() const;

        bool contains(const T& val) const;

      private:
        T* array;
        uint32 capacity;
        uint32 size;
    };
} // namespace blitz