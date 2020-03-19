#include <core/ogl/OpenGLDataType.h>

namespace blitz::ogl
{
    GLenum mapToGLDataType(const DataType& dataType)
    {
        switch (dataType)
        {
        case DataType::UBYTE:
            return GL_UNSIGNED_BYTE;
        case DataType::BYTE:
            return GL_BYTE;
        case DataType::INT:
            return GL_INT;
        case DataType::UINT:
            return GL_UNSIGNED_INT;
        case DataType::DOUBLE:
            return GL_DOUBLE;
        case DataType::FLOAT:
            return GL_FLOAT;
        case DataType::VECTOR2I:
            return GL_INT_VEC2;
        case DataType::VECTOR3I:
            return GL_INT_VEC3;
        case DataType::VECTOR2F:
            return GL_FLOAT_VEC2;
        case DataType::VECTOR3F:
            return GL_FLOAT_VEC3;
        case DataType::VECTOR4F:
            return GL_FLOAT_VEC4;
        case DataType::MATRIX4F:
            return GL_FLOAT_MAT4;
        case DataType::MATRIX3F:
            return GL_FLOAT_MAT3;
        }

        assert(0);
        return 0;
    }

    DataType mapToBlitzDataType(const GLenum& dataType)
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
        case GL_INT_VEC2:
            return DataType::VECTOR2I;
        case GL_INT_VEC3:
            return DataType::VECTOR3I;
        case GL_FLOAT_VEC3:
            return DataType::VECTOR3F;
        case GL_FLOAT_VEC4:
            return DataType::VECTOR4F;
        case GL_FLOAT_MAT4:
            return DataType::MATRIX4F;
        case GL_FLOAT_MAT3:
            return DataType::MATRIX3F;
        case GL_UNSIGNED_BYTE:
            return DataType::UBYTE;
        case GL_BYTE:
            return DataType::BYTE;
        default:
            assert(0);
            return DataType::UNKNOWN;
        }
    }

    uint8 getSizeInBytesFor(DataType dataType)
    {
        switch (dataType)
        {
        case DataType::UBYTE:
        case DataType::BYTE:
            return 1;
        case DataType::INT:
        case DataType::UINT:
        case DataType::FLOAT:
            return 4;
        case DataType::DOUBLE:
            return 8;
        case DataType::VECTOR2F:
        case DataType::VECTOR2I:
            return 8;
            return 8;
        case DataType::VECTOR3F:
            return 12;
        case DataType::VECTOR4F:
            return 16;
        case DataType::MATRIX3F:
            return 64;
        case DataType::MATRIX4F:
            return 48;
        }

        assert(0);
        return 0;
    }


#ifndef NDEBUG

    static const struct typeToNameEntry
    {
        GLenum type;
        const char* name;
    } typeToNameTable[] = { GL_FLOAT,
                            "float",
                            GL_FLOAT_VEC2,
                            "vec2",
                            GL_FLOAT_VEC3,
                            "vec3",
                            GL_FLOAT_VEC4,
                            "vec4",
                            GL_DOUBLE,
                            "double",
                            GL_DOUBLE_VEC2,
                            "dvec2",
                            GL_DOUBLE_VEC3,
                            "dvec3",
                            GL_DOUBLE_VEC4,
                            "dvec4",
                            GL_INT,
                            "int",
                            GL_INT_VEC2,
                            "ivec2",
                            GL_INT_VEC3,
                            "ivec3",
                            GL_INT_VEC4,
                            "ivec4",
                            GL_UNSIGNED_INT,
                            "uint",
                            GL_UNSIGNED_INT_VEC2,
                            "uvec2",
                            GL_UNSIGNED_INT_VEC3,
                            "uvec3",
                            GL_UNSIGNED_INT_VEC4,
                            "uvec4",
                            GL_BOOL,
                            "bool",
                            GL_BOOL_VEC2,
                            "bvec2",
                            GL_BOOL_VEC3,
                            "bvec3",
                            GL_BOOL_VEC4,
                            "bvec4",
                            GL_NONE,
                            NULL };

    const char* typeToName(GLenum type)
    {
        for (const typeToNameEntry* ptr = &typeToNameTable[0]; ptr->name != NULL; ++ptr)
        {
            if (ptr->type == type)
                return ptr->name;
        }

        return NULL;
    }

#endif
} // namespace blitz::ogl