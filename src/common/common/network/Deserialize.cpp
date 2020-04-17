#include "Deserialize.hpp"

namespace Net {

Common::Entity deserializeEntity(const std::vector<u8>& data) {
    const u32 tmpX{static_cast<u32>(data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24))};
    const u32 tmpY{static_cast<u32>(data[4] | (data[5] << 8) | (data[6] << 16) | (data[7] << 24))};
    Common::Entity entity;
    entity.x = *reinterpret_cast<const float*>(&tmpX);
    entity.y = *reinterpret_cast<const float*>(&tmpY);
    entity.type = data[8];
    entity.texID = data[9];
    entity.EID = data[10];
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

}
