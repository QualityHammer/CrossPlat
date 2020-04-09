#pragma once

#include "render/RenderTypes.h"
#include <common/GameMap.h>

namespace Client {

class GameState {
public:
    GameState();
    
    Player player;
    Common::GameMap gMap;
};

}
