#pragma once

#include <ResourcePtr.h>

namespace blitz
{
    template <typename T>
    class ResourceLoader
    {
    public:
        virtual T* load() = 0;
        virtual const ResourceID getID() const = 0 ;
        virtual ~ResourceLoader() = default;
    };
} // namespace blitz