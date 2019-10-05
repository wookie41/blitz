#include <core/ogl/GLDataType.h>
#include <loguru.hpp>

namespace blitz
{
    GLint mapToGLDataType(const DataType& dataType)
    {
        switch (dataType)
        {
        case DataType::INT:
            return GL_INT;
        case DataType::UINT:
            return GL_UNSIGNED_INT;
        case DataType::DOUBLE:
            return GL_DOUBLE;
        case DataType::FLOAT:
            return GL_FLOAT;
        case DataType::VECTOR3F:
            return GL_FLOAT_VEC3;
        case DataType::VECTOR4F:
            return GL_FLOAT_VEC4;
        case DataType::MATRIX4F:
            return GL_FLOAT_MAT4;
        case DataType::MATRIX3F:
            return GL_FLOAT_MAT3;
        }
    }

    DataType mapToBlitzDataType(const GLint& dataType)
    {
        switch (dataType)
        {
        case GL_INT:
            return DataType::INT;
        case GL_UNSIGNED_INT:
            return DataType::UINT;
        case GL_DOUBLE:
            return DataType::DOUBLE;
        case GL_FLOAT:
            return DataType::FLOAT;
        case GL_FLOAT_VEC3:
            return DataType::VECTOR3F;
        case GL_FLOAT_VEC4:
            return DataType::VECTOR4F;
        case GL_FLOAT_MAT4:
            return DataType::MATRIX4F;
        case GL_FLOAT_MAT3:
            return DataType::MATRIX3F;

        default:
            DLOG_F(INFO, "Unhandled type %ud", dataType);
        }
    }
} // namespace blitz