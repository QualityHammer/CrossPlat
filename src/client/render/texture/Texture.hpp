#pragma once

#include <string>

#include "../Pixels.hpp"

namespace Client {

// A texture contains multiple square pictures all
// concatenated in a line.
//
// A pixel from one of these pictures can be indexed using getPixel(x, y, texID).
class Texture {
public:
    // Initializes empty texture
    Texture();
    // Initializes texture from a file.
    // Offset should be the number of currently loaded pictures.
    Texture(const std::string filename, const u8 IDOffset);
    
    // Returns pixel data from a location in one of the pictures.
    const Color& getPixel(const u8 x, const u8 y, const u8 texID) const;

    // The entire pixel data for the texture.
    Pixels pixels;
    // The amount of pixels in the texture.
    size_t size;
    // The amount of pictures in the texture.
    size_t count;
    // The offset used to calculate texture IDs.
    u8 texIDOffset;
};

}
