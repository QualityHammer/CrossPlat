#pragma once

#include <vector>

#include "../GameState.hpp"
#include "texture/TextureManager.hpp"
#include "Pixels.hpp"
#include "Sprite.hpp"
#include <common/constructs/Types.hpp>
#include <common/constructs/GameMap.hpp>

namespace Client {

void render(const GameState& gameState, Pixels& pixels,
            const TextureManager& tMan, const std::vector<Sprite>& sprites);

}
