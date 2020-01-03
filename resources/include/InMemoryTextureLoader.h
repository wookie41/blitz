#pragma once

#include <ResourceLoader.h>
#include <blitzcommon/DataType.h>

namespace blitz
{
    class Texture;

    class InMemoryTextureLoader : ResourceLoader<Texture>
    {
      public:
        InMemoryTextureLoader(const BytesBuffer& buffer);

        Texture* load() override;
        const ResourceID getID() const override;

        ~InMemoryTextureLoader() override = default;

      private:
        ResourceID startingAddressAsInt;
        BytesBuffer bytesBuffer;
    };
} // namespace blitz