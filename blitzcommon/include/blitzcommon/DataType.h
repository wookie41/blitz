#pragma once

#include <cstdint>

#include <mathfu/glsl_mappings.h>

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
        VECTOR2I,
        VECTOR2F,
        VECTOR3F,
        VECTOR4F,
        MATRIX3F,
        MATRIX4F,
        SAMPLER1D,
        SAMPLER2D,
        SAMPLER3D,
    	BOOL
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
    using Vector2f = mathfu::vec2;
    using Vector2i = mathfu::vec2i;
    using Vector3f = mathfu::vec3;
    using Vector4f = mathfu::vec4;
    using Vector3i = mathfu::vec3i;
    using Vector4i = mathfu::vec4i;
    using Matrix3f = mathfu::mat3;
    using Matrix4f = mathfu::mat4;
    using uintptr = uintptr_t;
	
    struct BytesBuffer
    {
        size_t size;
        void* dataLocation;
    };

#define ToUint8(x) static_cast<uint8>(x)
#define ToUint16(x) static_cast<uint16>(x)
#define ToUint32(x) static_cast<uint32>(x)
#define ToUint64(x) static_cast<uint64>(x)
	
} // namespace blitz