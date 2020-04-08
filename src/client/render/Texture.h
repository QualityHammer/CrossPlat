#pragma once

#include <string>

#include "Image.h"

namespace Client {

class Texture {
public:
    Texture();
    Texture(const std::string filename);
    
    const Color& getSingleColor(const size_t texID) const;

    Pixels pixels;
    size_t size;
    size_t count;
};

}
