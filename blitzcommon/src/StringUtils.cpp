#include <blitzcommon/StringUtils.h>

namespace blitz
{
    size_t lastIndexOf(const char* str, const char chr)
    {
        int idx = 0;
        int lastIdx = -1;
        while (true)
        {
            if (str[idx] == '\0')
            {
                return lastIdx;
            }

            if (str[idx] == chr)
            {
                lastIdx = idx;
            }

            ++idx;
        };
    };
} // namespace blitz