#include "Texture.h"

#include "../Image.h"
#include "TextureErrors.h"

namespace Client {

Texture::Texture() {}

Texture::Texture(const std::string filename) {
    if (!loadTexture(filename, pixels,
                     size, count)) {
        TextureError(filename);
    }
}

const Color& Texture::getSingleColor(const size_t texID) const {
    return pixels[texID * size];
}

}