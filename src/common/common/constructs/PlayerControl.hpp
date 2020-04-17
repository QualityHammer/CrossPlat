#pragma once

#include "Types.hpp"

namespace Common {

// Represents a client's player movement
// during a frame.
struct PlayerControl {
    // Movement in X direction
    i8 moveX;
    // Movement in Y direction
    i8 moveY;
    // Amount to turn
    i8 turn;
};

}
