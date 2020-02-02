#include <core/TextureSampler.h>

namespace blitz
{
    TextureSampler::TextureSampler(Texture* t) : texture(t) {}

    Texture *TextureSampler::getTexture() const
    {
        return texture;
    }
} // namespace blitz