#ifndef BLITZ_REF_COUNTED_RESOURCE_MANAGER
#define BLITZ_REF_COUNTED_RESOURCE_MANAGER


#include <ResourcesManager.h>
#include <unordered_map>

namespace blitz
{

    template <typename T>
    class RefCountedResourceManager : public ResourcesManager<T>
    {
      public:
        ResourceID loadResource(ResourceLoader<T>* resourceLoader) override;
        ResourcePtr<T> getResource(const ResourceID& id) override;

        virtual ~RefCountedResourceManager() = default;

      private:
        std::unordered_map<ResourceID, ResourcePtr<T>> loadedResources;
        std::unordered_map<ResourceID, ResourceLoader<T>*> usedLoaders;
    };
} // namespace blitz

#include <RefCountedResourceManager.txx>

#endif