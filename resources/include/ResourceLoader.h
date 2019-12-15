#pragma once

#include <Resource.h>

namespace blitz
{
    class ResourceLoader
    {
    public:
        virtual Resource* load() = 0;
        virtual ResourceID getID() = 0;
        virtual ~ResourceLoader() = default;
    };
} // namespace blitz