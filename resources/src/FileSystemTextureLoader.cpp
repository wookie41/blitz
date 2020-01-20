#include <FileSystemTextureLoader.h>
#include <blitzcommon/HashUtils.h>
#include <InMemoryTextureLoader.h>


namespace blitz
{

    FileSystemTextureLoader::FileSystemTextureLoader(char *textureFilePath, bool mmapFile) :texturePath(textureFilePath),
    shouldMmap(mmapFile),
    pathHash(hashString(textureFilePath)){

    }


    Texture *FileSystemTextureLoader::load()
	{ return nullptr;
    }

    const ResourceID FileSystemTextureLoader::getID() const {
        return pathHash;
    }
}