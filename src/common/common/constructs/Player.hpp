#pragma once

#include "Entity.hpp"
#include "Types.hpp"

namespace Common {

// Represents a player in the game.
struct Player : public Entity {
    // View angle
    float a;
    // Player ID
    u8 PID;
    
    u8 bytes() const { return Entity::bytes() + sizeof(float) + sizeof(u8); }
};

}
