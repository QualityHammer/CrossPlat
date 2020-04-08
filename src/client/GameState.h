#pragma once

#include "render/RenderTypes.h"

namespace Client {

class GameState {
public:
    GameState();
    
    Player player;
    MapData gMap;
};

}
