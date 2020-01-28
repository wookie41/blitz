#include <blitzcommon/HashUtils.h>

namespace blitz
{
    hash hashString(const char* const str)
    {
        unsigned int h;
        unsigned char* p;

        h = 0;
        for (p = (unsigned char* const)str; *p != '\0'; p++)
            h = 37 * h + *p;

        return h;
    }
}