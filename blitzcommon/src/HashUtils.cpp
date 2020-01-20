#include <blitzcommon/HashUtils.h>

namespace blitz
{
    uint32 hashString(const char* str)
    {
        unsigned int h;
        unsigned char* p;

        h = 0;
        for (p = (unsigned char*)str; *p != '\0'; p++)
            h = 37 * h + *p;
        return h;
    }
}