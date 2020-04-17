#pragma once

#include <vector>

#include "../GameState.hpp"
#include "texture/TextureManager.hpp"
#include "Pixels.hpp"
#include "Sprite.hpp"
#include <common/constructs/Types.hpp>
#include <common/constructs/GameMap.hpp>

namespace Client {

// Renders everything to the screen pixel data based on the game state.
void render(const GameState& gameState, Pixels& pixels,
            const TextureManager& tMan, const std::vector<Sprite>& sprites);

}
