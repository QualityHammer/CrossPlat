#pragma once

#include <vector>

#include "../GameState.h"
#include "texture/TextureManager.h"
#include "Pixels.h"
#include "Sprite.h"
#include <common/Types.h>
#include <common/GameMap.h>

namespace Client {

void render(const GameState& gameState, Pixels& pixels,
            const TextureManager& tMan, const std::vector<Sprite>& sprites);

}
