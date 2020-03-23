#pragma once

#include <blitzcommon/DataType.h>
#include <blitzcommon/HashUtils.h>

namespace blitz
{
    template <typename T>
    struct Array
    {
        explicit Array(const uint32& arrCapacity);

        ~Array();

        T* get(const size_t& idx) const;
        void reserve(const size_t& amount);

        T* operator[](const size_t& idx) const;
        T* getArray() const;

        void add(T* val);
        void add(const T& val);

        void grow(const uint8& growFactor = 2);

        uint32 getSize() const;
        uint32 getCapacity() const;

        bool contains(const T& val) const;

      private:
        T* array;
        uint32 capacity;
        uint32 size;
    };

    template <typename T>
    struct HashEntry
    {
        hash key;
        T* value;
    };

    template <typename T>
    struct HashTable
    {
        HashTable();

        // returns nullptr if key is not present in the hash table
        T* operator[](const hash& key);
        T* set(const hash& key, T* value);

      private:
        uint16 numElements = 0;
        Array<HashEntry<T>>* hashTable;
    };


    template <typename T>
    Array<T>::Array(const uint32& arrCapacity)
    {
        array = new T[arrCapacity];
        bzero(array, sizeof(T) * arrCapacity);
        size = 0;
        capacity = arrCapacity;
    }

    template <typename T>
    void Array<T>::grow(const uint8& growFactor)
    {
        size_t newSize = size * growFactor;
        T* newArray = new T[newSize];
        memcpy(newArray, array, sizeof(T) * size);
        bzero(newArray + (size * sizeof(T)), sizeof(T) * (newSize - size));
        delete array;
        array = newArray;
        size = newSize;
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
    void Array<T>::reserve(const size_t& amount)
    {
        assert(size + amount <= capacity);
        size += amount;
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
        assert(size < capacity);
        array[size++] = *val;
    }

    template <typename T>
    void Array<T>::add(const T& val)
    {
        assert(size < capacity);
        array[size++] = std::move(val);
    }

    template <typename T>
    HashTable<T>::HashTable()
    {
        hashTable = new Array<HashEntry<T>>(16);
        hashTable->reserve(16);
    }

    template <typename T>
    T* HashTable<T>::operator[](const hash& key)
    {
        return hashTable->get(key % hashTable->getSize())->value;
    }

    template <typename T>
    T* HashTable<T>::set(const hash& key, T* value)
    {
        if (numElements == hashTable->getSize())
        {
            hashTable->grow();
            hashTable->reserve(hashTable->getCapacity());

            // rehash
            for (size_t entryIdx = 0; entryIdx < numElements; ++entryIdx)
            {
                HashEntry<T>* hashEntry = hashTable->get(entryIdx);

                hash key = hashEntry->key;
                T* value = hashEntry->value;
                hashEntry->value = nullptr;

                hashEntry = hashTable->get(key % hashTable->getSize());
                hashEntry->key = key;
                hashEntry->value = value;
            }
        }

        HashEntry<T>* hashEntry = hashTable->get(key % hashTable->getSize());
        assert(hashEntry->value == nullptr);

        hashEntry->key = key;
        hashEntry->value = value;

        ++numElements;
    }

} // namespace blitz