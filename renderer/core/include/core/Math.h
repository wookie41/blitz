#pragma once

#include <mathfu/matrix.h>
#include <mathfu/vector.h>

namespace blitz
{
    using Vector3f = mathfu::Vector<float, 3>;
    using Vector4f = mathfu::Vector<float, 4>;
    using Vector3i = mathfu::Vector<std::uint32_t , 3>;
    using Vector4i = mathfu::Vector<std::uint32_t , 4>;
    using Matrix3f = mathfu::Matrix<float, 3>;
    using Matrix4f = mathfu::Matrix<float, 4>;
    using Matrix3i = mathfu::Matrix<std::uint32_t , 3>;
    using Matrix4i = mathfu::Matrix<std::uint32_t , 4>;
}