#include <resources/ResourcesHolder.h>

namespace blitz
{
    ResourcesHolder::ResourcesHolder(const uint32& numResources) : capacity(numResources)
    {
        resources = new void*[numResources];
    }
    ResourcesHolder::~ResourcesHolder()
    {
        release();
        delete[] resources;
    }

    void ResourcesHolder::release()
    {
        for (uint32 idx = 0; idx < resourcesCount; ++idx)
        {
            delete resources[idx];
        }

        resourcesCount = 0;
    }

    void ResourcesHolder::resize(const uint32& size)
    {
        delete[] resources;
        resources = new void*[size];
        capacity = size;
        resourcesCount = 0;
    }

    const uint32 ResourcesHolder::getCapacity() const { return capacity; }


    void ResourcesHolder::add(void* resource)
    {
        assert(resourcesCount < capacity);
        resources[resourcesCount++] = resource;
    }

} // namespace core