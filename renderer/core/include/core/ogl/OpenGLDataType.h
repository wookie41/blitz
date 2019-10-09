#pragma once

#include <GL/glew.h>
#include <core/DataType.h>

namespace blitz
{
    GLenum mapToGLDataType(const DataType& dataType);
    DataType mapToBlitzDataType(const GLenum & dataType);
    const char* typeToName(GLenum type);
}