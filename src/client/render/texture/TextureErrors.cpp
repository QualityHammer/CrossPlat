#include "TextureErrors.hpp"

#include <iostream>

extern void TextureError(const std::string filename) {
    std::cerr << filename
        << " failed to load."
        << std::endl;
}
