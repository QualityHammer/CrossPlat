#include "TextureManager.hpp"

#include <cassert>

namespace Client {

TextureManager::TextureManager() : textureCount{0},
m_filenames{{
    "walls_sunroom.png",
    "walls_kitchen.png",
    "mitt.png",
    "peach.png"
}}, m_textures{} {
    assert(m_filenames.size() ==
           static_cast<size_t>(TextureName::NAME_COUNT));
    m_textures.resize(static_cast<size_t>(TextureName::NAME_COUNT));
    for (size_t i{0}; i < m_filenames.size(); i++) {
        m_textures[i] = Texture{m_filenames[i], textureCount};
        textureCount += m_textures[i].count;
    }
}

const Texture& TextureManager::operator[](const u8 texID) const {
    assert(texID < textureCount);
    for (u8 i{static_cast<u8>(TextureName::NAME_COUNT) - 1};
        i >= 0; i--){
        if (texID >= m_textures[i].texIDOffset)
            return m_textures[i];
    }
           return m_textures[0];
}

const u8& TextureManager::offset(const u8 texID) const {
    for (int i{static_cast<int>(m_textures.size() - 1)};
         i >= 0; --i) {
        if (m_textures[i].texIDOffset <= texID)
           return m_textures[i].texIDOffset;
    }
    return m_textures[0].texIDOffset;
}

}
