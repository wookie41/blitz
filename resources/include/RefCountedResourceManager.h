#pragma once

#include <ResourcesManager.h>
#include <unordered_map>

namespace blitz
{
    class ResourceLoader;

    class RefCountedResourceManager : public ResourcesManager
    {
      public:
        ResourceID loadResource(ResourceLoader* resourceLoader) override;

        Resource* getResource(ResourceID id) override;

        virtual ~RefCountedResourceManager() = default;

    private:
        std::unordered_map<ResourceID, ResourcePtr> loadedResources;
        std::unordered_map<ResourceID, ResourceLoader*> usedLoaders;
    };
} // namespace blitz