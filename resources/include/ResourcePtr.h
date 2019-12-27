#ifndef BLITZ_RESOURCE_PTR
#define BLITZ_RESOURCE_PTR

#include <blitzcommon/DataType.h>
#include <mutex>

namespace blitz
{
    using ResourceID = uint32;

    template <typename T>
    class ResourcePtr
    {
    public:
        explicit ResourcePtr(T* ptr);

        ResourcePtr(const ResourcePtr<T>& rhs);

        ResourcePtr(ResourcePtr<T>&& rhs) noexcept;

        ResourcePtr<T>& operator=(const ResourcePtr<T>& rhs);

        ResourcePtr<T>& operator=(ResourcePtr<T>&& rhs) noexcept;

        inline bool isExpired() const;

        T* operator->() const;

        void setResourcePtr(T* resourcePtr);

        virtual ~ResourcePtr();

        ResourcePtr& move(ResourcePtr& rhs);

    private:
        void decrementUsageCount();

        ResourcePtr& copy(const ResourcePtr& rhs);

        void release();

        std::mutex* counterMx = nullptr;
        uint32* usageCountPtr = nullptr;
        T* resourcePtr = nullptr;
    };
} // namespace blitz
#include <ResourcePtr.txx>

#endif


