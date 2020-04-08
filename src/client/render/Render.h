#pragma once

#include "../GameState.h"
#include "TextureManager.h"
#include "RenderTypes.h"
#include <common/Types.h>

namespace Client {

void followRay(Pixels& pixels, const float& angle, const Player& player,
                const MapData& gMap, const TextureManager& tMan,
                const u16& rayNum);

void render(const GameState& gameState, Pixels& pixels,
            const TextureManager& tMan);

Pixels textureColumn(const Pixels& pixels, const size_t texSize,
                   const size_t texNum, const size_t texID,
                   const TextureName name, const u16 coordX,
                   const u16 columnHeight);

}
