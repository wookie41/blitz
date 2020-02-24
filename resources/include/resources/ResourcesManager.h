#pragma once

#include <resources/Precompiled.h>

namespace blitz
{
    template <typename>
    class ResourceLoader;

    // ResourceManager's sole resposibility is to hold pointers to resources
    // that may be used in different places or by different components
    // of the system


    // ITS NOT resposible for managing the lifecycle of the resouce
    // the above should be handled by the thing that loaded the resource
    // for example, there might be a thing that loades all the needed resources
    // befora a level begins

    template <typename T>
    class ResourcesManager : public NonCopyable
    {
      public:
        // ResourceID is 0 if a resource couldn't be loaded
        ResourceID loadResource(ResourceLoader<T>* resourceLoader) = 0;
        // the return values indicates wether the resource was present at all
        bool releaseResource(const ResourceID& id);
        T* getResource(const ResourceID& id) = 0;
    };
} // namespace blitz