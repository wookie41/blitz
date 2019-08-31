#pragma once

#include "blitzcommon/Utils.h"

namespace blitz
{
    class Context : private NonCopyable
    {
      public:
        virtual ~Context() = default;
    };
} // namespace blitz