#pragma once

#include "render/Pixels.hpp"
#include <common/constructs/GameMap.hpp>
#include <common/constructs/Player.hpp>

namespace Client {

// Contains all data needed to render everything
// to the screen.
class GameState {
public:
    // Initialize
    GameState();
    
    // Player data
    Common::Player player;
    // Game map data
    Common::GameMap gMap;
};

}
