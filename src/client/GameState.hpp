#pragma once

#include "render/Player.hpp"
#include "render/Pixels.hpp"
#include <common/constructs/GameMap.hpp>

namespace Client {

class GameState {
public:
    GameState();
    
    Player player;
    Common::GameMap gMap;
};

}
