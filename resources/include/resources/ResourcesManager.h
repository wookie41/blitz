#pragma once

#include <resources/ResourcePtr.h>
#include <blitzcommon/NonCopyable.h>

namespace blitz
{
    template <typename> class ResourceLoader;

    template <typename T>
    class ResourcesManager: public NonCopyable
    {
    public:
        //ResourceID is 0 if a resource couldn't be loaded
        virtual ResourceID loadResource(ResourceLoader<T>* resourceLoader) = 0;
        virtual ResourcePtr<T> getResource(const ResourceID& id) = 0;
    };
} // namespace blitz