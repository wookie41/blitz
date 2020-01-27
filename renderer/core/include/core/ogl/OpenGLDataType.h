#pragma once

#include <GL/glew.h>
#include <blitzcommon/DataType.h>

#define ToGLSize(x) static_cast<GLsizei>(x)

namespace blitz::ogl
{
    GLenum mapToGLDataType(const DataType& dataType);
    DataType mapToBlitzDataType(const GLenum & dataType);
    const char* typeToName(GLenum type);
    uint8 getSizeInBytesFor(DataType dataType);
}