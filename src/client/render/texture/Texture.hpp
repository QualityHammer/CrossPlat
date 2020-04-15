#pragma once

#include <string>

#include "../Pixels.hpp"

namespace Client {

class Texture {
public:
    Texture();
    Texture(const std::string filename, const u8 texIDOffset);
    
    const Color& getPixel(const u8 x, const u8 y, const u8 texID) const;

    Pixels pixels;
    size_t size;
    size_t count;
    u8 texIDOffset;
};

}
