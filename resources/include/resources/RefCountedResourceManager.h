#ifndef BLITZ_REF_COUNTED_RESOURCE_MANAGER
#define BLITZ_REF_COUNTED_RESOURCE_MANAGER

#include <resources/Precompiled.h>
#include <resources/ResourcesManager.h>

namespace blitz
{

    template <typename T>
    class RefCountedResourceManager : public ResourcesManager<T>
    {
      public:
        ResourceID loadResource(ResourceLoader<T>* resourceLoader) override;
        ResourcePtr<T> getResource(const ResourceID& id) override;

        virtual ~RefCountedResourceManager();

      private:
        std::unordered_map<ResourceID, ResourcePtr<T>> loadedResources;
        std::unordered_map<ResourceID, ResourceLoader<T>*> usedLoaders;
    };
} // namespace blitz

#include <resources/RefCountedResourceManager.txx>

#endif
