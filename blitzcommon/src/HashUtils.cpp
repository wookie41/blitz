#include <blitzcommon/HashUtils.h>

namespace blitz
{
    hash hashString(const char* const str, const size_t strLen)
    {
        unsigned int h;

        h = 0;
        for (size_t idx = 0; str[idx] != '\0' && (strLen > 0 ? idx < strLen : true); ++idx)
            h = 37 * h + str[idx];

        return h;
    }
} // namespace blitz