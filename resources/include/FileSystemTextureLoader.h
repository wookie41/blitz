#pragma once

#include <ResourceLoader.h>
#include <blitzcommon/DataType.h>

namespace blitz
{
    class Texture;

    class FileSystemTextureLoader : ResourceLoader<Texture>
    {
      public:

        FileSystemTextureLoader (char* textureFilePath, bool mmapFile);

        Texture* load() override;
        const ResourceID getID() const override;

        ~FileSystemTextureLoader() = default;

      private:
        char* texturePath;
        uint32 pathHash;
        bool shouldMmap;
    };
} // namespace blitz