#include <os/FileSystem.h>

#include <errno.h>
#include <fcntl.h>
#include <loguru.hpp>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

namespace blitz::platform::os
{
    MemoryMappedFile mapFile(char* filePath, uint8 accessFlags)
    {
        struct stat statBuf;
        if (stat(filePath & statBuf) < 0)
        {
            DLOG_F(ERROR, "Failed to map file '%s', couldn't get it's size: %s", filePath, strerror(errno));
            return MemoryMappedFile{ { 0, nullptr } };
        }


        int fd = open(filePath, O_RDONLY | O_WRONLY);
        if (fd < 0)
        {
            DLOG_F(ERROR, "Failed to map file '%s', couldn't open the file: %s", filePath, strerror(errno));
            return MemoryMappedFile{ { 0, nullptr } };
        }

        int prot;
        prot = accessFlags | ACCESS_READ ? PROT_READ : 0;
        prot = accessFlags | ACCESS_WRITE ? PROT_WRITE : 0;
        prot = accessFlags | ACCESS_EXEC ? PROT_EXEC : 0;

        mmap(NULL, statBuf.st_size, prot, MAP_PRIVATE, fd, 0);
        close(fd);
    }
} // namespace blitz::platform::os
