#pragma once

#include "../GameState.h"
#include "texture/TextureManager.h"
#include "RenderTypes.h"
#include <common/Types.h>
#include <common/GameMap.h>

namespace Client {

void render(const GameState& gameState, Pixels& pixels,
            const TextureManager& tMan);

}
