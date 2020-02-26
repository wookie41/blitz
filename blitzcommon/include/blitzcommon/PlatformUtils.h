#ifndef BLITZ_PLATFORM_UTILS_H
#define BLITZ_PLATFORM_UTILS_H

#include <blitzcommon/DataType.h>
#include <blitzcommon/StringUtils.h>

namespace blitz
{
    namespace fs
    {

#ifdef WIN32
        const char SEPARATOR = '\\';
#else
        const char SEPARATOR = '/';
#endif

        struct FilePath
        {
            // name of the file, null terminated
            char* fileName;
            // null terminator is not included
            size_t fileNameLength;
            // directory with trailing slash, null terminated
            char* directoryPath;
            // null terminator is not included
            size_t directoryPathLength;

            ~FilePath()
            {
                delete[] fileName;
                delete[] directoryPath;
            }
        };

        void seperateFileNameAndPath(const char* filePath, FilePath* path);
    } // namespace fs


} // namespace blitz

#endif