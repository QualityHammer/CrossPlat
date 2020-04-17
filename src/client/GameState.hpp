#pragma once

#include "render/Player.hpp"
#include "render/Pixels.hpp"
#include <common/constructs/GameMap.hpp>

namespace Client {

// Contains all data needed to render everything
// to the screen.
class GameState {
public:
    // Initialize
    GameState();
    
    // Player data
    Player player;
    // Game map data
    Common::GameMap gMap;
};

}
