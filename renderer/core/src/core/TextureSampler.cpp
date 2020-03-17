#include <core/TextureSampler.h>
#include <core/Texture.h>

namespace blitz
{
    TextureSampler::TextureSampler(Texture* t) : texture(t) {}

    Texture* TextureSampler::getTexture() const
    {
        return texture;
    }
} // namespace blitz