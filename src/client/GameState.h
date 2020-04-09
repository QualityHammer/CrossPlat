#pragma once

#include "render/Player.h"
#include "render/Pixels.h"
#include <common/constructs/GameMap.h>

namespace Client {

class GameState {
public:
    GameState();
    
    Player player;
    Common::GameMap gMap;
};

}
