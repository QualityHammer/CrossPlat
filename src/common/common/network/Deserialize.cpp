#include "Deserialize.hpp"

namespace Net {

Common::Entity deserializeEntity(const std::vector<u8>& data) {
    const u32 tmpX{static_cast<u32>(data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24))};
    const u32 tmpY{static_cast<u32>(data[4] | (data[5] << 8) | (data[6] << 16) | (data[7] << 24))};
    Common::Entity entity;
    entity.x = *reinterpret_cast<const float*>(&tmpX);
    entity.y = *reinterpret_cast<const float*>(&tmpY);
    entity.texID = data[8];
    return entity;
}

Common::GameMap deserializeGameMap(const std::vector<u8>& data) {
    Common::GameMap gMap;
    gMap.w = data[0];
    gMap.h = data[1];
    gMap.size = data[2] | (data[3] << 8);
    gMap.data.insert(gMap.data.end(), data.begin() + 4, data.end());
    return gMap;
}

Common::Player deserializePlayer(const std::vector<u8>& data) {
    const Common::Entity tmp{deserializeEntity(data)};
    Common::Player player;
    player.x = tmp.x;
    player.y = tmp.y;
    player.texID = tmp.texID;
    const u32 tmpA{static_cast<u32>(data[9] | (data[10] << 8) | (data[11] << 16) | (data[12] << 24))};
    player.a = *reinterpret_cast<const float*>(&tmpA);
    player.PID = data[13];
    return player;
}

Common::PlayerControl deserializePlayerControl(const std::vector<u8>& data) {
    Common::PlayerControl playerControl;
    playerControl.moveX = data[0];
    playerControl.moveY = data[1];
    const u32 tmpTurn{static_cast<u32>(data[2] | (data[3] << 8) | (data[4] << 16) | (data[5] << 24))};
    playerControl.turn = *reinterpret_cast<const float*>(&tmpTurn);
    return playerControl;
}

}
