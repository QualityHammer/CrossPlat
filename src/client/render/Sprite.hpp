#pragma once

#include <vector>

#include <common/constructs/Types.hpp>

namespace Client {

// WILL BE REPLACED BY ENTITY
// Representation of a sprite to render on screen.
struct Sprite {
    float x, y;
    u8 texID;
};

using Sprites = std::vector<Sprite>;

}
