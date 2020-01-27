#include <resources/RefCountedResourceManager.h>
#include <atomic>

namespace blitz
{
    template <typename T>
    ResourceID RefCountedResourceManager<T>::loadResource(ResourceLoader<T>* resourceLoader)
    {
        const auto resourceID = resourceLoader->getID();
        const auto isLoaded = loadedResources.find(resourceID) != loadedResources.end();
        if (isLoaded)
        {
            return resourceID;
        }

        const auto resourcePtr = resourceLoader->load();
        if (resourcePtr == nullptr)
        {
            return 0;
        }

        auto usageCount = new std::atomic<uint32>(0);

        loadedResources.insert({ resourceID, ResourcePtr(resourcePtr) });
        return resourceID;
    }

    template <typename T>
    ResourcePtr<T> RefCountedResourceManager<T>::getResource(const ResourceID& id)
    {
        const auto resourceIt = loadedResources.find(id);

        if (resourceIt == loadedResources.end())
        {
            return ResourcePtr<T>(nullptr);
        }

        // TODO this could load the resource back instead of throwin a nullptr

        if (resourceIt->second.isExpired())
        {
            return ResourcePtr<T>(nullptr);
        }
        return resourceIt->second;
    }
} // namespace blitz