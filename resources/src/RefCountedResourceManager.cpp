#include <RefCountedResourceManager.h>
#include <ResourceLoader.h>

namespace blitz
{
    static void noopDeleter(Resource*) {}

    ResourceID RefCountedResourceManager::loadResource(ResourceLoader* resourceLoader)
    {
        const auto resourceID = resourceLoader->getID();
        const auto isLoaded = loadedResources.find(resourceID) != loadedResources.end();
        if (isLoaded)
        {
            return resourceLoader->getID();
        }

        const auto loadedResource = resourceLoader->load();
        if (loadedResource == nullptr)
        {
            return 0;
        }

        std::shared_ptr<Resource> resourcePtr(loadedResource, &noopDeleter);
        loadedResources[resourceID] = std::weak_ptr(resourcePtr);
        return resourceID;
    }

    ResourcePtr RefCountedResourceManager::getResource(ResourceID id)
    {
        const auto resourceIt = loadedResources.find(id);
        if (resourceIt == loadedResources.end())
        {
            return ResourcePtr(nullptr);
        }
        return ResourcePtr(resourceIt->second);
    }
} // namespace blitz