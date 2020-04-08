#pragma once

#include <string>
#include <array>
#include <vector>

#include "Texture.h"

namespace Client {

enum class TextureName : size_t {
    WALL,
    NAME_COUNT
};

using TextureFiles = std::array<std::string,
static_cast<size_t>(TextureName::NAME_COUNT)>;
using TextureList = std::vector<Texture>;

class TextureManager {
public:
    TextureManager();
    
    const Texture& operator[](const TextureName name) const;
private:
    const TextureFiles m_filenames;
    TextureList m_textures;
};

}

