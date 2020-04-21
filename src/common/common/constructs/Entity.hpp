#pragma once

#include <vector>

#include "Types.hpp"

namespace Common {

// Represents either a static entity
// or a player.
struct Entity {
    // World position
    float x, y;
    u8 type;
    // ID used to pick texture for entity
    u8 texID;
    // Unique ID for each entity in a game
    u8 EID;
    
    u8 bytes() const { return sizeof(float) * 2 + sizeof(u8) * 3; }
};

using Entities = std::vector<Entity>;

}
