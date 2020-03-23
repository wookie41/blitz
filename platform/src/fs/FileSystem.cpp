#pragma once

#include <platform/fs/FileSystem.h>
#include <stdio.h>
#include <stdlib.h>

namespace blitz::fs
{
    char* readFile(const blitz::string& filePath)
    {
        char* retVal = nullptr;
        FILE* fileToRead = fopen(filePath, "rb");

        if (fileToRead == nullptr)
        {
            return nullptr;
        }
        fseek(fileToRead, 0, SEEK_END);

        char* buffer = nullptr;
        std::size_t numRead = 0;

        unsigned long fileSize = ftell(fileToRead);
        if (fileSize == -1)
        {
            goto readFileEnd;
        }

        rewind(fileToRead);

        buffer = new char[fileSize + 1];
        numRead = fread(buffer, 1, fileSize, fileToRead);

        if (numRead != fileSize)
        {
            delete[] buffer;
            goto readFileEnd;
        }

        buffer[fileSize] = '\0';
        retVal = buffer;

    readFileEnd:
        fclose(fileToRead);
        return retVal;
    }
} // namespace blitz::fs