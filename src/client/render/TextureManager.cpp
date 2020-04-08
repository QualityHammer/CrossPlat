#include "TextureManager.h"

#include <cassert>

namespace Client {

TextureManager::TextureManager() : m_filenames{
    "walltext.png"
}, m_textures{} {
    assert(m_filenames.size() ==
           static_cast<size_t>(TextureName::NAME_COUNT));
    m_textures.resize(static_cast<size_t>(TextureName::NAME_COUNT));
    for (size_t i{0}; i < m_filenames.size(); i++) {
        m_textures[i] = Texture{m_filenames[i]};
    }
}

const Texture& TextureManager::operator[](const TextureName name) const {
    assert(name < TextureName::NAME_COUNT);
    return m_textures[static_cast<size_t>(name)];
}

}
