#include "Player.hpp"

#include <cassert>

#include "../network/Serialize.hpp"
#include "../network/Deserialize.hpp"

namespace Common {

Net::Packet& operator<<(Net::Packet& packet, const Common::Player& player) {
    assert(packet.type == Net::PacketType::PLAYER || packet.type == Net::PacketType::NONE);
    if (packet.type == Net::PacketType::NONE) {
        packet.type = Net::PacketType::PLAYER;
    }
    
    const std::vector<u8> serialized{Net::serialize(player)};
    packet.data.insert(packet.data.end(), serialized.begin(), serialized.end());
    
    packet.size += player.bytes();
    
    return packet;
}

Net::Packet& operator>>(Net::Packet& packet, Common::Player& player) {
    assert(packet.type == Net::PacketType::PLAYER);
    assert(packet.size > 0);
    
    const std::vector<u8> tmp{packet.data.begin(), packet.data.begin() + player.bytes()};
    const Player tmpPla{Net::deserializePlayer(tmp)};
    player.x = tmpPla.x;
    player.y = tmpPla.y;
    player.texID = tmpPla.texID;
    player.a = tmpPla.a;
    player.PID = tmpPla.PID;
    
    packet.data.erase(packet.data.begin(), packet.data.begin() + player.bytes());
    packet.size -= player.bytes();
    
    return packet;
}

}
