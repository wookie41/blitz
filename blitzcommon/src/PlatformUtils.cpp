#include <blitzcommon/PlatformUtils.h>

namespace blitz
{
    namespace fs
    {

        void seperateFileNameAndPath(const char* filePath, FilePath* path)
        {
            assert(path != nullptr);

            size_t lastSeparatorIndex = lastIndexOf(filePath, SEPARATOR);
            if (lastSeparatorIndex == -1)
            {
                path->fileNameLength = strlen(filePath);
                path->fileName = (char*)malloc(path->fileNameLength + 1);
                strncpy(path->fileName, filePath, path->fileNameLength);

                path->directoryPathLength = 0;
                path->directoryPath = (char*)malloc(1);
                path->directoryPath[0] = '\0';
                return;
            }

            size_t filePathLength = strlen(filePath);
            path->fileNameLength = filePathLength - lastSeparatorIndex - 1;
            path->fileName = (char*)malloc(path->fileNameLength + 1);
            path->fileName[path->fileNameLength] = '\0';
            strncpy(path->fileName, filePath + lastSeparatorIndex + 1, path->fileNameLength);

            path->directoryPathLength = lastSeparatorIndex + 1;
            path->directoryPath = (char*)malloc(path->directoryPathLength + 1);
            path->directoryPath[path->directoryPathLength] = '\0';
            strncpy(path->directoryPath, filePath, path->directoryPathLength);
        }

    } // namespace fs


} // namespace blitz