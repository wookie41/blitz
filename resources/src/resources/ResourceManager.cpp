#include <resources/ResourcesManager.h>

namespace blitz
{
    template <typename T>
    ResourceID ResourceManager<T>::loadResource(ResourceLoader<T>* resourceLoader)
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

        loadedResources.insert({ resourceID, ResourcePtr(resourcePtr) });
        return resourceID;
    }

    template <typename T>
    ResourcePtr<T> ResourceManager<T>::getResource(const ResourceID& id)
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

    template <typename T>
    ResourceManager<T>::~ResourceManager()
    {
        for (const auto loaderIt : usedLoaders)
        {
            delete loaderIt.second;
        }
    }
} // namespace blitz