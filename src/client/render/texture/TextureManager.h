#pragma once

#include <string>
#include <array>
#include <vector>

#include "Texture.h"

namespace Client {

enum class TextureName : size_t {
    SUNROOM,
    KITCHEN,
    MITT,
    PEACH,
    NAME_COUNT
};

using TextureFiles = std::array<std::string,
static_cast<size_t>(TextureName::NAME_COUNT)>;
using TextureList = std::vector<Texture>;

class TextureManager {
public:
    TextureManager();
    
    u8 textureCount;
    
    const u8& offset(const u8 texID) const;
    
    const Texture& operator[](const u8 texID) const;
private:
    const TextureFiles m_filenames;
    TextureList m_textures;
};

}

