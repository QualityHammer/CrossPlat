#include "Texture.hpp"

#include "../Image.hpp"
#include "TextureErrors.hpp"

namespace Client {

Texture::Texture() {}

Texture::Texture(const std::string filename, const u8 texIDOffset)
: texIDOffset{texIDOffset} {
    if (!loadTexture(filename, pixels,
                     size, count)) {
        TextureError(filename);
    }
}

const Color& Texture::getPixel(const u8 x, const u8 y, const u8 texID) const {
    return pixels[(x + (texID - texIDOffset) * size) + (y * size * count)];
}

}
