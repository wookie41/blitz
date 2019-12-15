#pragma once

#include <blitzcommon/NonCopyable.h>
#include <Resource.h>

namespace blitz
{
    class ResourceLoader;

    class ResourcesManager: public NonCopyable
    {
    public:
        //ResourceID is 0 if a resource couldn't be loaded
        virtual ResourceID loadResource(ResourceLoader* resourceLoader) = 0;
        virtual Resource* getResource(ResourceID) = 0;
    };
} // namespace blitz