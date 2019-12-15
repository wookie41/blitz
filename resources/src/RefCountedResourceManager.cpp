#include <RefCountedResourceManager.h>
#include <ResourceLoader.h>

namespace blitz
{
    static void noopDeleter(ResourcePtr*) {}

    ResourceID RefCountedResourceManager::loadResource(ResourceLoader* resourceLoader)
    {
        const auto resourceID = resourceLoader->getID();
        const auto isLoaded = loadedResources.find(resourceID) != loadedResources.end();
        if (isLoaded)
        {
            return resourceID;
        }

        const auto loadedResource = resourceLoader->load();
        if (loadedResource == nullptr)
        {
            return 0;
        }

        loadedResources[resourceID] = new ResourcePtr(resourceID, loadedResource);
        return std::shared_ptr<Resource>(loadedResource);
    }

    ResourcePtr RefCountedResourceManager::getResource(ResourceID id)
    {
        const auto resourceIt = loadedResources.find(id);

        if (resourceIt == loadedResources.end())
        {
            return ResourcePtr(nullptr);
        }

        // TODO this could load the resource back instead of throwin a nullptr
 
        if (resourceIt->second.expired())
        {
            return ResourcePtr(nullptr);

        }
        return ResourcePtr(resourceIt->second);
    }
} // namespace blitz