#pragma once

#define M_PI 3.14159265358979323846

namespace blitz
{
    constexpr const auto RAD_IN_DEG = M_PI / 180.f;

    inline float toRadians(const float& degrees) 
    {
        return degrees * RAD_IN_DEG;
    }   
}