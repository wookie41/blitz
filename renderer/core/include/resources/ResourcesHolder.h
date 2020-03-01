#pragma once

#include <core/Precompiled.h>

/*
 this class is responsible for holding GPU resources and related
 it's just a simple pointer storage that frees the memory when asked
 it's supposed with avoiding problems of double free, or just
 freeing related object that are no longer needed at the same time
 for now, the implementation doesn't allow to insert the same pointer several times
 if a pointer is added multiple times, then double will occur
 we could use a set or something, but that's not the point of this class
 this class should be used by something like a level loader, that loads a bunch of models
 and want to be sure that the memory for them will be freed once the level complets
*/

namespace blitz
{
    class ResourcesHolder
    {
      public:
        explicit ResourcesHolder(const uint32& numResources);
        ~ResourcesHolder();

        void add(void* resource);
        const uint32 getCapacity() const;

        void release();

        // this method assumes that release() have been called, as it doesn't cleanup before resizing
        void resize(const uint32& size);

      private:
        uint32 capacity;
        uint32 resourcesCount;
        void** resources = nullptr;
    };
} // namespace blitz