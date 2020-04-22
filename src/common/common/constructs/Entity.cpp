#include "Entity.hpp"

#include <cassert>

#include "../network/Serialize.hpp"
#include "../network/Deserialize.hpp"

namespace Common {

Net::Packet& operator<<(Net::Packet& packet, const Common::Entity& entity) {
    assert(packet.type == Net::PacketType::ENTITY || packet.type == Net::PacketType::NONE);
    if (packet.type == Net::PacketType::NONE) {
        packet.type = Net::PacketType::ENTITY;
    }

    const std::vector<u8> serialized{Net::serialize(entity)};
    packet.data.insert(packet.data.end(), serialized.begin(), serialized.end());

    packet.size += entity.bytes();

    return packet;
}

Net::Packet& operator>>(Net::Packet& packet, Common::Entity& entity) {
    assert(packet.type == Net::PacketType::ENTITY);
    assert(packet.size > 0);

    const std::vector<u8> tmp{packet.data.begin(), packet.data.begin() + entity.bytes()};
    const Entity tmpEnt{Net::deserializeEntity(tmp)};
    entity.x = tmpEnt.x;
    entity.y = tmpEnt.y;
    entity.texID = tmpEnt.texID;

    packet.data.erase(packet.data.begin(), packet.data.begin() + entity.bytes());
    packet.size -= entity.bytes();

    return packet;
}

}
