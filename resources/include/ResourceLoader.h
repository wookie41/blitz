#pragma once

#include <blitzcommon/NonCopyable.h>

namespace blitz
{
    class Resource;

    class ResourceLoader : public NonCopyable
    {
    public:
        virtual Resource* load() = 0;
    };
} // namespace blitz