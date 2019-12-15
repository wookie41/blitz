#pragma once

#include <blitzcommon/DataType.h>
#include <mutex>

namespace blitz
{
    using ResourceID = uint32;

    class Resource
    {
      public:

        explicit Resource(ResourceID id);

        ResourceID getID() const;

        virtual ~Resource() = default;

      protected:
        ResourceID id;
    };

    class ResourcePtr
    {

        friend class RefCountedResourceManager;

      public:
        explicit ResourcePtr(Resource* ptr);

        ResourcePtr(const ResourcePtr& rhs);

        ResourcePtr(ResourcePtr&& rhs) noexcept;

        ResourcePtr& operator=(const ResourcePtr& rhs);

        ResourcePtr& operator=(ResourcePtr&& rhs) noexcept;

        inline bool isExpired() const;

        Resource* operator->() const;

        void setResourcePtr(Resource* resourcePtr);

        virtual ~ResourcePtr();

      private:

        void decrementUsageCount();

        ResourcePtr& copy(const ResourcePtr& rhs);

        ResourcePtr& move(ResourcePtr& rhs);

        void release();

        std::mutex* counterMx = nullptr;
        uint32* usageCountPtr = nullptr;
        Resource* resourcePtr = nullptr;

    };
} // namespace blitz