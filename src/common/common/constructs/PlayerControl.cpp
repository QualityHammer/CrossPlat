#include "PlayerControl.hpp"

#include <cassert>

#include "../network/Deserialize.hpp"
#include "../network/Serialize.hpp"

namespace Common {

Net::Packet& operator<<(Net::Packet& packet, const Common::PlayerControl& playerControl) {
    assert(packet.type == Net::PacketType::PLAYER_CONTROL || packet.type == Net::PacketType::NONE);
    if (packet.type == Net::PacketType::NONE) {
        packet.type = Net::PacketType::PLAYER_CONTROL;
    }
    
    const std::vector<u8> serialized{Net::serialize(playerControl)};
    packet.data.insert(packet.data.end(), serialized.begin(), serialized.end());
    
    packet.size += playerControl.bytes();
    
    return packet;
}

Net::Packet& operator>>(Net::Packet& packet, Common::PlayerControl& playerControl) {
    assert(packet.type == Net::PacketType::PLAYER_CONTROL);
    assert(packet.size > 0);
    
    const std::vector<u8> tmp{packet.data.begin(), packet.data.begin() + playerControl.bytes()};
    playerControl = Net::deserializePlayerControl(tmp);
    
    packet.data.erase(packet.data.begin(), packet.data.begin() + playerControl.bytes());
    packet.size -= playerControl.bytes();
    
    return packet;
}

}
