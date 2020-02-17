#pragma once

#include <resources/texture/TextureLoader.h>

namespace blitz
{
    class Texture;

    class STBImage2DTextureLoader : public TextureLoader
    {
      public:
        explicit STBImage2DTextureLoader(const ResourceLocation& location);

        Texture* load() override;
        const ResourceID getID() const override;

        ~STBImage2DTextureLoader() = default;

      private:
        ResourceID textureID;
    };
} // namespace blitz