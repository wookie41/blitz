#pragma once

#include <blitzcommon/DataType.h>

namespace blitz
{
    //str - null terminated string
    //char - to look for
    //return idx of 'chr' or -1 if not found
    size_t lastIndexOf(const char* str, const char chr);
    char* copyStr(const char* toCpy);
}