#include "Render.h"

#include "../ClientOptions.h"
#include <cmath>
#include <cassert>
#include <algorithm>

namespace Client {

void renderRect(Pixels& pixels, const u16 x,
                const u16 y, const u16 w,
                const u16 h, const Color color) {
    assert(pixels.size() ==
           WINDOW_WIDTH * WINDOW_HEIGHT);
    for (u16 i{0}; i < w; i++) {
        for (u16 j{0}; j < h; j++) {
            u16 cx{static_cast<u16>(x + i)};
            u16 cy{static_cast<u16>(y + j)};
            if (cx >= WINDOW_WIDTH ||
                cy >= WINDOW_HEIGHT) continue;
            pixels[cx + cy *
                   WINDOW_WIDTH] = color;
        }
    }
}

void render(const GameState& gameState, Pixels& pixels,
            const TextureManager& tMan) {
    const Player& player{gameState.player};
    const MapData& gMap{gameState.gMap};
    
    std::fill(pixels.begin(), pixels.end(), 0);
    for (u16 i{0}; i < WINDOW_WIDTH; i++) {
        float angle{player.a - FOV / 2 + FOV * i /
            (float)WINDOW_WIDTH
        };
        for (float t{0.0}; t < 20.0; t += 0.05) {
            float cx{player.x + t * std::cos(angle)};
            float cy{player.y + t * std::sin(angle)};
            int index{(int)cx + (int)cy * MAP_WIDTH};
            if (gMap[index] != ' ') {
                size_t texID{static_cast<size_t>(gMap[index] - '0')};
                const Texture& texture{tMan[TextureName::WALL]};
                u16 columnHeight{
                    static_cast<u16>(WINDOW_HEIGHT /
                                     (t * std::cos(angle - player.a)))};
                renderRect(pixels, i,
                           WINDOW_HEIGHT / 2 - columnHeight,
                           1, columnHeight * 2,
                           texture.getSingleColor(texID));
                break;
                
            }
        }
    }
}

}
