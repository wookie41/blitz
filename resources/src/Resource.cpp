#include <Resource.h>
#include <cassert>
#include <cstdint>

namespace blitz
{
    Resource::Resource(ResourceID id) : id(id) {}

    ResourceID Resource::getID() const { return id; }


    ResourcePtr::ResourcePtr(Resource* ptr)
    {
        counterMx = new std::mutex();
        usageCountPtr = new uint32_t;
        *usageCountPtr = 0;
        resourcePtr = ptr;
    }

    ResourcePtr::ResourcePtr(const ResourcePtr& rhs) { copy(rhs); }

    ResourcePtr::ResourcePtr(ResourcePtr&& rhs) noexcept { move(rhs); }

    ResourcePtr& ResourcePtr::operator=(const ResourcePtr& rhs) { return copy(rhs); }

    ResourcePtr& ResourcePtr::operator=(ResourcePtr&& rhs) noexcept { return move(rhs); }

    Resource* ResourcePtr::operator->() const { return resourcePtr; }

    bool ResourcePtr::isExpired() const { return *usageCountPtr == 0; }

    void ResourcePtr::setResourcePtr(Resource* resourcePtr)
    {
        assert(this->resourcePtr == nullptr);
        this->resourcePtr = resourcePtr;
    }

    ResourcePtr::~ResourcePtr() { decrementUsageCount(); }

    void ResourcePtr::release()
    {
        if (*usageCountPtr > 0)
            return;

        delete usageCountPtr;
        delete counterMx;
        delete resourcePtr;
    }


    ResourcePtr& ResourcePtr::copy(const ResourcePtr& rhs)
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

    ResourcePtr& ResourcePtr::move(ResourcePtr& rhs)
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

    void ResourcePtr::decrementUsageCount()
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
} // namespace blitz
