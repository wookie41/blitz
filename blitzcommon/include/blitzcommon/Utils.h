#pragma once

namespace blitz
{
    class NonCopyable
    {
    public:
        NonCopyable() = default;
        NonCopyable(const NonCopyable& other) = delete;
        NonCopyable& operator=(const NonCopyable* other) = delete;
    };
}