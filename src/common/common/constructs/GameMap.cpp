#include "GameMap.hpp"

#include <cassert>

#include "../network/Deserialize.hpp"
#include "../network/Serialize.hpp"

namespace Common {

const u8& GameMap::operator[](const u16 index) const {
    return data[index];
}

Net::Packet& operator<<(Net::Packet& packet, const Common::GameMap& gameMap) {
    assert(packet.type == Net::PacketType::GAME_MAP || packet.type == Net::PacketType::NONE);
    if (packet.type == Net::PacketType::NONE) {
        packet.type = Net::PacketType::GAME_MAP;
    }
    
    const std::vector<u8> serialized{Net::serialize(gameMap)};
    packet.data.insert(packet.data.end(), serialized.begin(), serialized.end());
    
    packet.size += gameMap.bytes();
    
    return packet;
}

Net::Packet& operator>>(Net::Packet& packet, Common::GameMap& gameMap) {
    assert(packet.type == Net::PacketType::GAME_MAP);
    assert(packet.size > 0);
    
    const std::vector<u8> tmp{packet.data.begin(), packet.data.end()};
    gameMap = Net::deserializeGameMap(tmp);
    
    packet.data.erase(packet.data.begin(), packet.data.end());
    packet.size -= gameMap.bytes();
    
    return packet;
}

}
