#include "Serialize.hpp"

namespace {

void serializeFloat(const float& f, std::vector<u8>& data, const u16 offset) {
    for (u8 i{0}; i < sizeof(float); ++i) {
        data[i + offset] = (*reinterpret_cast<const u32*>(&f) & (0xff << (i * 8))) >> (i * 8);
    }
}

void serializeU16(const u16& i, std::vector<u8>& data, const u16 offset) {
    data[offset] = i & 0xff;
    data[offset + 1] = (i & 0xff00) >> 8;
}

}

namespace Net {

const std::vector<u8> serialize(const Common::Entity& entity) {
    std::vector<u8> data{};
    data.resize(entity.bytes());
    
    serializeFloat(entity.x, data, 0);
    serializeFloat(entity.y, data, sizeof(float));
    serializeFloat(entity.velX, data, sizeof(float) * 2);
    serializeFloat(entity.velY, data, sizeof(float) * 3);
    data[sizeof(float) * 4] = entity.texID;
    
    return data;
}

const std::vector<u8> serialize(const Common::GameMap& gMap) {
    std::vector<u8> data;
    data.resize(sizeof(u16) + 2);
    
    data[0] = gMap.w;
    data[1] = gMap.h;
    serializeU16(gMap.size, data, 2);
    data.insert(data.end(), gMap.data.begin(), gMap.data.end());
    
    return data;
}

const std::vector<u8> serialize(const Common::Player& player) {
    std::vector<u8> data{serialize(reinterpret_cast<const Common::Entity&>(player))};
    data.resize(player.bytes());
    
    const u8 entityBytes{reinterpret_cast<const Common::Entity&>(player).bytes()};
    serializeFloat(player.a, data, entityBytes);
    data[sizeof(float) + entityBytes] = player.PID;
    
    return data;
}

const std::vector<u8> serialize(const Common::PlayerControl& playerControl) {
    std::vector<u8> data{};
    data.resize(playerControl.bytes());
    
    data[0] = playerControl.moveX;
    data[1] = playerControl.moveY;
    serializeFloat(playerControl.turn, data, 2);
    
    return data;
}

}
