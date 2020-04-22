#pragma once

#include <vector>

#include "Types.hpp"

namespace Common {

// Represents either a static entity
// or a player.
struct Entity {
    // World position
    float x, y;
    // ID used to pick texture for entity
    u8 texID;
    
    u8 bytes() const { return sizeof(float) * 2 + sizeof(u8); }
};

}
