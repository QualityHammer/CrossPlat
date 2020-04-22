#pragma once

#include "Types.hpp"
#include "../network/Packet.hpp"

namespace Common {

// Represents a client's player movement
// during a frame.
struct PlayerControl {
    // Movement in X direction
    i8 moveX;
    // Movement in Y direction
    i8 moveY;
    // Amount to turn
    float turn;
    
    u8 bytes() const { return sizeof(i8) * 2 + sizeof(float); }

    friend Net::Packet& operator<<(Net::Packet& packet, const Common::PlayerControl& playerControl);
    friend Net::Packet& operator>>(Net::Packet& packet, Common::PlayerControl& playerControl);
};

}
