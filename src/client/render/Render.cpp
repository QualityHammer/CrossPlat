#include "Render.hpp"

#include <cmath>
#include <cassert>
#include <algorithm>

#include "../ClientOptions.hpp"
#include <common/constructs/Entity.hpp>

namespace Client {

Pixels textureColumn(const Texture& texture, const u8 texID, const u16 coordX,
                     const u16 columnHeight, const u8 offset) {
    const size_t imgW{texture.size * texture.count};
    const size_t imgH{texture.size};
    assert(texture.pixels.size() == imgW * imgH && coordX < texture.size &&
           texID - offset < texture.count);
    Pixels column{};
    column.resize(columnHeight);
    for (size_t y{0}; y < columnHeight; y++) {
        size_t px{(texID) * texture.size + coordX};
        size_t py{(y * texture.size) / columnHeight};
        column[y] = texture.pixels[px + py * imgW];
    }
    return column;
}

void renderColumn(Pixels& pixels, const Common::GameMap& gMap, const TextureManager& tMan,
                  const Common::Player& player, const float& cx, const float& cy, const float& angle,
                  const float& dist, const u16 rayNum, int& px, int& py, const int& mapIndex) {
    // The id for the texture to use for this column
    u8 texID{static_cast<u8>(gMap[mapIndex] - 1)};
    // Prevent overflow
    if (texID >= tMan.textureCount) texID = 0;
    const Texture& texture{tMan[texID]};
    u16 columnHeight{static_cast<u16>(WINDOW_HEIGHT / (dist * std::cos(angle - player.a)))};
    // Prevent column overflow
    if (columnHeight > WINDOW_HEIGHT) columnHeight = WINDOW_HEIGHT;
    // The position where the ray has hit a wall
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
    textureColumn(texture, texID, coordX, columnHeight, tMan.offset(texID));
    px = rayNum;
    // Display column
    for (size_t j{0}; j < columnHeight; j++) {
        py = j + WINDOW_HEIGHT / 2 - columnHeight / 2;
        if (py < 0 || py >= (int)WINDOW_HEIGHT) continue;
        pixels[px + py * WINDOW_WIDTH] = column[j];
    }
}

void followRay(Pixels& pixels, const float& angle, const Common::Player& player,
               const Common::GameMap& gMap, const TextureManager& tMan, const u16& rayNum,
               std::array<u16, WINDOW_WIDTH>& distanceBuffer) {
    // Follow ray until a wall is hit
    for (float t{0.0}; t < 20.0; t += 0.02) {
        float cx{player.x + t * std::cos(angle)};
        float cy{player.y + t * std::sin(angle)};
        int px{static_cast<int>(cx * WINDOW_WIDTH / gMap.w)};
        int py{static_cast<int>(cy * WINDOW_HEIGHT / gMap.h)};
        const int mapIndex{(int)cx + (int)cy * gMap.w};
        // Render column on screen when a wall is hit
        if (gMap[mapIndex] != 0) {
            distanceBuffer[rayNum] = (u16)t;
            renderColumn(pixels, gMap, tMan, player, cx, cy, angle, t, rayNum, px, py,mapIndex);
            break;
            
        }
    }
}

void renderSprite(const Common::Player& player, Pixels& pixels, const Common::Entity& entity, const Texture& texture,
                  const std::array<u16, WINDOW_WIDTH>& distanceBuffer) {
    // Direction from player to sprite
    float spriteDir{std::atan2(entity.y - player.y, entity.x - player.x)};
    // Remove unneeded radians
    while (spriteDir - player.a > M_PI) spriteDir -= 2 * M_PI;
    while (spriteDir - player.a < -M_PI) spriteDir += 2 * M_PI;
    
    // Distance from player to sprite
    float spriteDist{static_cast<float> (std::sqrt(pow(player.x - entity.x, 2) +
                                                   pow(player.y - entity.y, 2)))};
    // Width/ height of sprite on screen
    u16 spriteScreenSize{std::min(WINDOW_HEIGHT, static_cast<u16>(WINDOW_HEIGHT / spriteDist))};
    // Top left position of sprite on screen
    i16 xOff{static_cast<i16>((spriteDir - player.a) / FOV * WINDOW_WIDTH + WINDOW_WIDTH / 2 - texture.size / 2)};
    i16 yOff{static_cast<i16>(WINDOW_HEIGHT / 2 - spriteScreenSize / 2)};
    
    // Draw sprite to screen buffer
    for (u16 i{0}; i < spriteScreenSize; i++) {
        if (xOff + (int)i < 0 || xOff + i >= WINDOW_WIDTH) continue; // Sprite offscreen
        if (distanceBuffer[xOff + i] < spriteDist) continue; // Sprite behind wall
        for (u16 j{0}; j < spriteScreenSize; j++) {
            if (yOff + (int)j < 0 || yOff + j >= WINDOW_HEIGHT) continue; // Sprite offscreen
            const Color& color{texture.getPixel(i * texture.size / spriteScreenSize,
                                                j * texture.size / spriteScreenSize,
                                                entity.texID)};
            if (color >> 24 > 128)
                pixels[xOff + i + ((yOff + j) * WINDOW_WIDTH)] = color;
        }
    }
}

void render(const GameState& gameState, Pixels& pixels, const TextureManager& tMan) {
    const Common::Player& player{gameState.player};
    const Common::GameMap& gMap{gameState.gMap};
    
    // Fill top and bottom background colors
    std::fill(pixels.begin(), pixels.end() - pixels.size() / 2, 0xf05aaac8);
    std::fill(pixels.begin() + pixels.size() / 2, pixels.end(), 0xf0336699);
    
    std::array<u16, WINDOW_WIDTH> distanceBuffer{};
    // Draw walls
    for (u16 i{0}; i < WINDOW_WIDTH; i++) {
        float angle{player.a - FOV / 2 + FOV * i / (float)WINDOW_WIDTH
        };
        followRay(pixels, angle, player, gMap, tMan, i, distanceBuffer);
    }
    
    // Draw sprites
    for (const auto& pair : gameState.entities) {
        renderSprite(player, pixels, pair.second, tMan[pair.second.texID], distanceBuffer);
    }
}

}
