#include "Deserialize.hpp"
namespace {

float deserializeFloat(const std::vector<u8>& data, const u16 offset) {
    const u32 tmp{static_cast<u32>(data[offset] | (data[offset + 1] << 8) | (data[offset + 2] << 16) | (data[offset + 3] << 24))};
    return *reinterpret_cast<const float*>(&tmp);
}

u16 deserializeU16(const std::vector<u8>& data, const u16 offset) {
    return data[offset] | (data[offset + 1] << 8);
}

}

namespace Net {

Common::Entity deserializeEntity(const std::vector<u8>& data) {
    Common::Entity entity;
    entity.x = deserializeFloat(data, 0);
    entity.y = deserializeFloat(data, sizeof(float));
    entity.texID = data[sizeof(float) * 2];
    return entity;
}

Common::GameMap deserializeGameMap(const std::vector<u8>& data) {
    Common::GameMap gMap;
    gMap.w = data[0];
    gMap.h = data[1];
    gMap.size = deserializeU16(data, 2);
    gMap.data.insert(gMap.data.end(), data.begin() + sizeof(u16) + 2, data.end());
    return gMap;
}

Common::Player deserializePlayer(const std::vector<u8>& data) {
    const Common::Entity tmp{deserializeEntity(data)};
    Common::Player player;
    player.x = tmp.x;
    player.y = tmp.y;
    player.texID = tmp.texID;
    player.a = deserializeFloat(data, sizeof(float) * 2 + 1);
    player.PID = data[sizeof(float) * 3 + 1];
    return player;
}

Common::PlayerControl deserializePlayerControl(const std::vector<u8>& data) {
    Common::PlayerControl playerControl;
    playerControl.moveX = data[0];
    playerControl.moveY = data[1];
    playerControl.turn = deserializeFloat(data, 2);
    return playerControl;
}

}
