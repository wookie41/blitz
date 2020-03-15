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

    char* copyStr(const char* toCpy)
    {
        const auto len = strlen(toCpy);
        char* copied = new char[len + 1];
        strncpy(copied, toCpy, len);
        copied[len] = '\0';
        return copied;
    }

    string::string(const char* str) : strPtr(str)
    {
        length = strlen(str);
        strHash = hashString(strPtr);
    }

    size_t string::getLength() const { return length; }
    string::operator char*() const { return strPtr; }

    bool string::operator==(const string& rhs) const { return strHash == rhs.strHash; }

    char string::operator[](const size_t idx) const { return strPtr[idx]; }

    hash string::getHash() const { return strHash; }

} // namespace blitz