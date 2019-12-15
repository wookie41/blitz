#pragma once

#include <Resource.h>
#include <blitzcommon/NonCopyable.h>

namespace blitz
{
    class ResourceLoader;

    class ResourcesManager: public NonCopyable
    {
    public:
        //ResourceID is 0 if a resource couldn't be loaded
        virtual ResourceID loadResource(ResourceLoader* resourceLoader) = 0;
        virtual ResourcePtr getResource(const ResourceID& id) = 0;
    };
} // namespace blitz