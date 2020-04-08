#pragma once

#include "../GameState.h"
#include "Image.h"
#include "TextureManager.h"
#include <common/Types.h>

namespace Client {

void renderRect(Pixels& pixels, const u16 x,
                const u16 y, const u16 w,
                const u16 h, const Color color);

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
