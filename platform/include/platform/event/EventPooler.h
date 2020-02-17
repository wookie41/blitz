#pragma once

#include <blitzcommon/NonCopyable.h>

namespace blitz::platform
{
    class EventPooler : public NonCopyable
    {
      public:
        virtual void poolEvents() = 0;

        virtual ~EventPooler() = default;
    };
} // namespace blitz::platform
