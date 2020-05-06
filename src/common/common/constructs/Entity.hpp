#pragma once

#include <vector>

#include "../network/Packet.hpp"
#include "Types.hpp"

namespace Common {

// Represents either a static entity
// or a player.
struct Entity {
    // World position
    float x, y;
    // World velocity
    float velX, velY;
    // ID used to pick texture for entity
    u8 texID;
    
    u8 bytes() const { return sizeof(float) * 4 + sizeof(u8); }

    friend Net::Packet& operator<<(Net::Packet& packet, const Common::Entity& entity);
    friend Net::Packet& operator>>(Net::Packet& packet, Common::Entity& entity);
};

}
