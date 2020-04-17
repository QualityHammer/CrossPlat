#pragma once

#include "Types.hpp"

namespace Common {

// Represents a player in the game.
struct Player {
    // World position
    float x, y;
    // View angle
    float a;
    // Entity ID
    u8 EID;
    
    static u8 bytes() { return sizeof(float) * 3 + sizeof(u8); }
};

}
