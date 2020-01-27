#pragma once

#include <resources/ResourcePtr.h>
#include <blitzcommon/DataType.h>

namespace blitz
{
    struct ResourceLocation
    {
        char* locationInMemory;
        char* pathToFile;
        size_t sizeInBytes;
    };

    template <typename T>
    class ResourceLoader
    {
      public:
        explicit ResourceLoader(const ResourceLocation& location);
        virtual T* load() = 0;
        virtual const ResourceID getID() const = 0;
        virtual ~ResourceLoader() = default;

    protected:	
        ResourceLocation resourceLocation;
    };

	template <typename T>
    ResourceLoader<T>::ResourceLoader(const ResourceLocation& location) : resourceLocation(location) {}
} // namespace blitz