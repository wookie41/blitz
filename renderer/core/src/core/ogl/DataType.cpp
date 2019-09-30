#include <core/ogl/DataType.h>
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
        }
    }

    DataType mapToBlitzDataType(const GLuint& dataType)
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
            default:
                DLOG_F(INFO, "Unhandled type %ud", dataType);
        }
    }
}