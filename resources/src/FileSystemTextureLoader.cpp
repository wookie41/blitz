#include <FileSystemTextureLoader.h>
#include <blitzcommon/HashUtils.h>
#include <InMemoryTextureLoader.h>


namespace blitz
{

    FileSystemTextureLoader::FileSystemTextureLoader(char *textureFilePath, bool mmapFile) :texturePath(textureFilePath),
    shouldMmap(mmapFile),
    pathHash(hashString(textureFilePath)){

    }


    Texture *FileSystemTextureLoader::load() {

        if (shouldMmap)
        {
            const auto mappedFileBuffer = os::mapFile
            const InMemoryTextureLoader inMemoryTextureLoader(mappedFileContents);
        }
    }

    const ResourceID FileSystemTextureLoader::getID() const {
        return pathHash;
    }
}