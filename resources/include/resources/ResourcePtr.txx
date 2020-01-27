#include <resources/ResourcePtr.h>
#include <cassert>
#include <cstdint>

namespace blitz
{
    template <typename T>
    ResourcePtr<T>::ResourcePtr(T* ptr)
    {
        counterMx = new std::mutex();
        usageCountPtr = new uint32_t;
        *usageCountPtr = 0;
        resourcePtr = ptr;
    }


    template <typename T>
    ResourcePtr<T>::ResourcePtr(const ResourcePtr<T>& rhs)
    {
        copy(rhs);
    }


    template <typename T>
    ResourcePtr<T>::ResourcePtr(ResourcePtr<T>&& rhs) noexcept
    {
        move(rhs);
    }

    template <typename T>
    ResourcePtr<T>& ResourcePtr<T>::operator=(const ResourcePtr<T>& rhs)
    {
        return copy(rhs);
    }

    template <typename T>
    ResourcePtr<T>& ResourcePtr<T>::operator=(ResourcePtr<T>&& rhs) noexcept
    {
        return move(rhs);
    }

    template <typename T>
    bool ResourcePtr<T>::isExpired() const
    {
        return *usageCountPtr == 0;
    }

    template <typename T>
    T* ResourcePtr<T>::operator->() const
    {
        return resourcePtr;
    }

    template <typename T>
    void ResourcePtr<T>::setResourcePtr(T* resourcePtr)
    {
        assert(this->resourcePtr == nullptr);
        this->resourcePtr = resourcePtr;
    }

    template <typename T>
    ResourcePtr<T>::~ResourcePtr()
    {
        decrementUsageCount();
    }

    template <typename T>
    ResourcePtr<T>& ResourcePtr<T>::move(ResourcePtr& rhs)
    {
        decrementUsageCount();

        this->resourcePtr = rhs.resourcePtr;
        this->usageCountPtr = rhs.usageCountPtr;
        this->counterMx = rhs.counterMx;

        rhs.usageCountPtr = nullptr;
        rhs.resourcePtr = nullptr;
        rhs.counterMx = nullptr;
        return *this;
    }

    template <typename T>
    void ResourcePtr<T>::decrementUsageCount()
    {

        if (counterMx == nullptr)
            return;

        {
            std::lock_guard<std::mutex> lock(*counterMx);

            if (!isExpired() && (--(*usageCountPtr)) == 0)
            {
                delete resourcePtr;
                resourcePtr = nullptr;
            }
        }
    }

    template <typename T>
    ResourcePtr<T>& ResourcePtr<T>::copy(const ResourcePtr& rhs)
    {
        decrementUsageCount();

        this->resourcePtr = rhs.resourcePtr;
        this->usageCountPtr = rhs.usageCountPtr;
        this->counterMx = rhs.counterMx;

        {
            std::lock_guard<std::mutex> lock(*counterMx);
            ++(*usageCountPtr);
        }

        return *this;
    }

    template <typename T>
    void ResourcePtr<T>::release()
    {
        if (*usageCountPtr > 0)
            return;

        delete usageCountPtr;
        delete counterMx;
        delete resourcePtr;
    }
} // namespace blitz