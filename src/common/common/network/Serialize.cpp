#include "Serialize.hpp"

const std::vector<u8> serialize(const Common::Entity& entity) {
    std::vector<u8> data{};
    data.resize(entity.bytes());
    
    for (u8 i{0}; i < sizeof(float); ++i) {
        data[i] = (*reinterpret_cast<const u32*>(&entity.x) & (0xff << (i * 8))) >> (i * 8);
    }
    for (u8 i{0}; i < sizeof(float); ++i) {
        data[i + sizeof(float)] = (*reinterpret_cast<const u32*>(&entity.y) & (0xff << (i * 8))) >> (i * 8);
    }
    data[8] = entity.texID;
    
    return data;
}

const std::vector<u8> serialize(const Common::GameMap& gMap) {
    std::vector<u8> data;
    data.resize(4);
    
    data[0] = gMap.w;
    data[1] = gMap.h;
    data[2] = gMap.size & 0xff;
    data[3] = (gMap.size & 0xff00) >> 8;
    data.insert(data.end(), gMap.data.begin(), gMap.data.end());
    
    return data;
}

const std::vector<u8> serialize(const Common::Player& player) {
    std::vector<u8> data{serialize(reinterpret_cast<const Common::Entity&>(player))};
    
    for (u8 i{0}; i < sizeof(float); ++i) {
        data.push_back((*reinterpret_cast<const u32*>(&player.a) & (0xff << (i * 8))) >> (i * 8));
    }
    data.push_back(player.PID);
    
    return data;
}

const std::vector<u8> serialize(const Common::PlayerControl& playerControl) {
    std::vector<u8> data;
    
    data.push_back(playerControl.moveX);
    data.push_back(playerControl.moveY);
    for (u8 i{0}; i < sizeof(float); ++i) {
        data.push_back((*reinterpret_cast<const u32*>(&playerControl.turn) & (0xff << (i * 8))) >> (i * 8));
    }
    
    return data;
}
