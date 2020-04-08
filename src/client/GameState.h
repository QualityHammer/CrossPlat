#pragma once

#include "RenderTypes.h"

namespace Client {

class GameState {
public:
    GameState();
    
    Player player;
    MapData gMap;
};

}
