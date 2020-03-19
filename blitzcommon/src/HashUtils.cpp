#include <blitzcommon/HashUtils.h>

namespace blitz
{
    hash hashString(const char* const str)
    {
        unsigned int h;

        h = 0;
        for (size_t idx = 0; str[idx] != '\0'; ++idx)
            h = 37 * h + str[idx];

        return h;
    }
} // namespace blitz