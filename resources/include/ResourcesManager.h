#pragma once

#include <blitzcommon/NonCopyable.h>
#include <Resource.h>
#include <memory>

namespace blitz
{
    using ResourcePtr = std::shared_ptr<Resource>;

    class ResourceLoader;

    class ResourcesManager: public NonCopyable
    {
    public:
        //ResourceID is 0 if a resource couldn't be loaded
        virtual ResourceID loadResource(ResourceLoader* resourceLoader) = 0;
        virtual ResourcePtr getResource(ResourceID) = 0;
    };
} // namespace blitz