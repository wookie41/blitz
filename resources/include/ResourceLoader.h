#pragma once

#include <blitzcommon/NonCopyable.h>
#include <Resource.h>

namespace blitz
{
    class ResourceLoader : public NonCopyable
    {
    public:
        virtual Resource* load() = 0;
        virtual ResourceID getID() = 0;
        virtual ~ResourceLoader() = default;
    };
} // namespace blitz