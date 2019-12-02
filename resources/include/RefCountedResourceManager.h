#pragma once

#include <ResourcesManager.h>
#include <blitzcommon/NonCopyable.h>
#include <unordered_map>

namespace blitz
{
    class ResourceLoader;

    class RefCountedResourceManager : public ResourcesManager
    {
      public:
        ResourceID loadResource(ResourceLoader* resourceLoader) override;

        ResourcePtr getResource(ResourceID id) override;

        virtual ~RefCountedResourceManager() = default;

    private:
        std::unordered_map<ResourceID, std::weak_ptr<Resource>> loadedResources;
        std::unordered_map<ResourceID, ResourceLoader*> usedLoaders;
    };
} // namespace blitz