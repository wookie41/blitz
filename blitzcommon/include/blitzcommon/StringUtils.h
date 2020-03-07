#pragma once

#include <blitzcommon/HashUtils.h>

namespace blitz
{
    // custom string class
    // the member strPtr not null terminated
    class string
    {
      public:
        string() = default;
        explicit string(char* str, const size_t& len);
        size_t getLength() const;
        operator char*() const;
        bool operator==(const string& rhs) const;
        char operator[](const size_t idx) const;
        hash getHash() const;


      private:
        size_t length = 0;
        char* strPtr = nullptr;
        hash strHash = 0;
    };

    // str - null terminated string
    // char - to look for
    // return idx of 'chr' or -1 if not found
    size_t lastIndexOf(const char* str, const char chr);
    char* copyStr(const char* toCpy);
} // namespace blitz
