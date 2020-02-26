#include <blitzcommon/StringUtils.h>

namespace blitz
{
    size_t lastIndexOf(const char* str, const char chr)
    {
        int idx = 0;
        while (true)
        {
            if (str[idx] == '\0')
            {
                return -1;
            }

            if (str[idx] == chr)
            {
                return idx;
            }

            ++idx;
        };
    };
} // namespace blitz