#pragma once

#include <GL/glew.h>
#include <core/DataType.h>

namespace blitz
{
    GLint mapToGLDataType(const DataType& dataType);
    DataType mapToBlitzDataType(const GLint& dataType);
}