#include "Render.h"

#include <cmath>
#include <cassert>
#include <algorithm>

#include "../ClientOptions.h"

namespace Client {

Pixels textureColumn(const Texture& texture, const size_t texID,
                   const u16 coordX, const u16 columnHeight) {
    const size_t imgW{texture.size * texture.count};
    const size_t imgH{texture.size};
    assert(texture.pixels.size() == imgW * imgH &&
           coordX < texture.size && texID < texture.count);
    Pixels column{};
    column.resize(columnHeight);
    for (size_t y{0}; y < columnHeight; y++) {
        size_t px{texID * texture.size + coordX};
        size_t py{(y * texture.size) / columnHeight};
        column[y] = texture.pixels[px + py * imgW];
    }
    return column;
}

void renderColumn(Pixels& pixels, const MapData& gMap,
                  const TextureManager& tMan,
                  const Player& player, const float& cx,
                  const float& cy, const float& angle,
                  const float& dist, const u16 rayNum,
                  int& px, int& py, const int& mapIndex) {
    size_t texID{static_cast<size_t>(gMap[mapIndex] - '0')};
    const Texture& texture{tMan[TextureName::WALL]};
    u16 columnHeight{
        static_cast<u16>(WINDOW_HEIGHT /
                         (dist * std::cos(angle - player.a)))};
    float hitX{cx - std::floor(cx + 0.5f)};
    float hitY{cy - std::floor(cy + 0.5f)};
    int coordX{static_cast<int>(hitX * texture.size)};
    // For vertical walls
    if (std::abs(hitY) > std::abs(hitX)) {
        coordX = hitY * texture.size;
    }
    if (coordX < 0) coordX += texture.size;
    assert(coordX >= 0 && coordX < (int)texture.size);
    
    std::vector<Color> column =
    textureColumn(texture, texID, coordX, columnHeight);
    px = WINDOW_WIDTH + rayNum;
    for (size_t j{0}; j < columnHeight; j++) {
        py = j + WINDOW_HEIGHT / 2 - columnHeight / 2;
        if (py < 0 || py >= (int)WINDOW_HEIGHT) continue;
        pixels[px + py * WINDOW_WIDTH] = column[j];
    }
}

void followRay(Pixels& pixels, const float& angle, const Player& player,
               const MapData& gMap, const TextureManager& tMan,
               const u16& rayNum) {
    for (float t{0.0}; t < 20.0; t += 0.05) {
        float cx{player.x + t * std::cos(angle)};
        float cy{player.y + t * std::sin(angle)};
        int px{static_cast<int>(cx * PIXEL_WIDTH)};
        int py{static_cast<int>(cy * PIXEL_HEIGHT)};
        const int mapIndex{(int)cx + (int)cy * MAP_WIDTH};
        if (gMap[mapIndex] != ' ') {
            renderColumn(pixels, gMap, tMan,
                         player, cx, cy, angle,
                         t, rayNum, px, py,
                         mapIndex);
            break;
            
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
        followRay(pixels, angle, player, gMap,
                  tMan, i);
    }
}

}
