#pragma once

#include <string>
#include <array>
#include <vector>

#include "Texture.hpp"

namespace Client {

// Each texture's name
enum class TextureName : size_t {
    SUNROOM,
    KITCHEN,
    MITT,
    PEACH,
    NAME_COUNT
};

using TextureFiles = std::array<std::string, static_cast<size_t>(TextureName::NAME_COUNT)>;
using TextureList = std::vector<Texture>;

// A manager used to contain all of the textures of a game.
class TextureManager {
public:
    // Initialize manager
    TextureManager();
    
    // The amount of textures in the manager.
    u8 textureCount;
    
    // Returns the offset for any texture ID.
    const u8& offset(const u8 texID) const;
    
    // Returns a texture using it's ID.
    const Texture& operator[](const u8 texID) const;
private:
    // A list of texture filenames.
    const TextureFiles m_filenames;
    // All of the textures being managed.
    TextureList m_textures;
};

}

