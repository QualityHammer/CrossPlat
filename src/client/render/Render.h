#pragma once

#include "../GameState.h"
#include "Image.h"
#include "TextureManager.h"
#include <common/Types.h>

namespace Client {

void renderRect(Pixels& pixels, const u16 x,
                const u16 y, const u16 w,
                const u16 h, const Color color);

void render(const GameState& gameState, Pixels& pixels,
            const TextureManager& tMan);

}
