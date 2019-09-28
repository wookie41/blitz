#include <core/ShaderSource.h>

namespace blitz
{

    ShaderSource::~ShaderSource() {
        delete name;
    }
}