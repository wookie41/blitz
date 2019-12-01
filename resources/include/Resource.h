#pragma once

#include <blitzcommon/DataType.h>

namespace blitz
{
    using ResourceID = uint32;

    class Resource
    {
      public:
        explicit Resource(ResourceID id);

        virtual void* getContent() = 0;

      private:
        ResourceID id;
    };
} // namespace blitz