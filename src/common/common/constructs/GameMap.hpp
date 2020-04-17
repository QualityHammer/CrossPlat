#pragma once

#include <vector>

#include "Types.hpp"

namespace Common {

// Representation of a map to be
// run in the game.
struct GameMap {
    // Width
    u16 w;
    // Height
    u16 h;
    // Total amount of 'tiles'
    u16 size;
    // Map data
    std::vector<u8> data;
    
    const u8& operator[](const u16 index) const;
};

}
