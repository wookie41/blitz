#pragma once

#include <cstdint>

#include <mathfu/matrix.h>
#include <mathfu/vector.h>

namespace blitz
{
    enum class DataType
    {
        UNKNOWN,
        BYTE,
        UBYTE,
        INT,
        UINT,
        FLOAT,
        DOUBLE,
        VECTOR3F,
        VECTOR4F,
        MATRIX3F,
        MATRIX4F,
        SAMPLER1D,
        SAMPLER2D,
        SAMPLER3D
    };

    using int8 = std::int8_t;
    using uint8 = std::int8_t;
    using int16 = std::int16_t;
    using uint16 = std::int16_t;
    using int32 = std::int32_t;
    using uint32 = std::uint32_t;
    using int64 = std::int64_t;
    using uint64 = std::uint64_t;
    using decimal = float;
    using size_t = std::size_t;
    using Vector2f = mathfu::Vector<float, 3>;
    using Vector2i = mathfu::Vector<uint32, 3>;
    using Vector3f = mathfu::Vector<float, 3>;
    using Vector4f = mathfu::Vector<float, 4>;
    using Vector3i = mathfu::Vector<uint32, 3>;
    using Vector3l = mathfu::Vector<uint64, 3>;
    using Vector4l = mathfu::Vector<uint64, 4>;
    using Vector4i = mathfu::Vector<uint32, 4>;
    using Matrix3f = mathfu::Matrix<float, 3>;
    using Matrix4f = mathfu::Matrix<float, 4>;
    using Matrix3i = mathfu::Matrix<uint32, 3>;
    using Matrix4i = mathfu::Matrix<uint32, 4>;
    using uintptr = uintptr_t;

    struct BytesBuffer
    {
        size_t size;
        void* dataLocation;
    };


} // namespace blitz