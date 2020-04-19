#include "Packet.hpp"

#include <cassert>

#include "Serialize.hpp"
#include "Deserialize.hpp"

namespace Net {

Packet::Packet() : status{PacketStatus::IDLE}, type{PacketType::NONE}, size{0}, data{} {}

ENetPacket* Packet::toENet() const {
    std::vector<u8> tmp{{static_cast<u8>(type), static_cast<u8>(size & 0xff), static_cast<u8>((size & 0xff00) >> 8)}};
    tmp.insert(tmp.end(), data.begin(), data.end());
    return enet_packet_create(tmp.data(), tmp.size(), ENET_PACKET_FLAG_RELIABLE);
}

Packet& Packet::operator<<(ENetPacket* enetPacket) {
    const u8* recv{reinterpret_cast<const u8*>(enetPacket->data)};
    type = static_cast<PacketType>(*recv);
    size = *(recv + 1) | (*(recv + 2) << 8);
    const u8 dataOffset{3};
    for (u16 i{dataOffset}; i < size + dataOffset; ++i)
        data.push_back(*(recv + i));
    enet_packet_destroy(enetPacket);
    status = PacketStatus::RECIEVED;
    return *this;
}

Packet& Packet::operator<<(const Common::Entity& entity) {
    assert(type == PacketType::ENTITY || type == PacketType::NONE);
    if (type == PacketType::NONE) {
        type = PacketType::ENTITY;
    }
    
    const std::vector<u8> serialized{serialize(entity)};
    data.insert(data.end(), serialized.begin(), serialized.end());
    
    size += Common::Entity::bytes();
    
    return *this;
}

Packet& Packet::operator<<(const Common::GameMap& gameMap) {
    assert(type == PacketType::GAME_MAP || type == PacketType::NONE);
    if (type == PacketType::NONE) {
        type = PacketType::GAME_MAP;
    }
    
    const std::vector<u8> serialized{serialize(gameMap)};
    data.insert(data.end(), serialized.begin(), serialized.end());
    
    size += gameMap.bytes();
    
    return *this;
}

Packet& Packet::operator<<(const Common::Player& player) {
    assert(type == PacketType::PLAYER || type == PacketType::NONE);
    if (type == PacketType::NONE) {
        type = PacketType::PLAYER;
    }
    
    const std::vector<u8> serialized{serialize(player)};
    data.insert(data.end(), serialized.begin(), serialized.end());
    
    size += Common::Player::bytes();
    
    return *this;
}

Packet& Packet::operator<<(const Common::PlayerControl& playerControl) {
    assert(type == PacketType::PLAYER_CONTROL || type == PacketType::NONE);
    if (type == PacketType::NONE) {
        type = PacketType::PLAYER_CONTROL;
    }
    
    const std::vector<u8> serialized{serialize(playerControl)};
    data.insert(data.end(), serialized.begin(), serialized.end());
    
    size += Common::PlayerControl::bytes();
    
    return *this;
}

Packet& Packet::operator>>(Common::Entity &entity) {
    assert(type == PacketType::ENTITY);
    assert(size > 0);
    
    const std::vector<u8> tmp{data.begin(), data.begin() + Common::Entity::bytes()};
    entity = deserializeEntity(tmp);
    
    data.erase(data.begin(), data.begin() + Common::Entity::bytes());
    size -= Common::Entity::bytes();
    
    return *this;
}

Packet& Packet::operator>>(Common::GameMap& gameMap) {
    assert(type == PacketType::GAME_MAP);
    assert(size > 0);
    
    const std::vector<u8> tmp{data.begin(), data.end()};
    gameMap = deserializeGameMap(tmp);
    
    data.erase(data.begin(), data.end());
    size -= gameMap.bytes();
    
    return *this;
}

Packet& Packet::operator>>(Common::Player& player) {
    assert(type == PacketType::PLAYER);
    assert(size > 0);
    
    const std::vector<u8> tmp{data.begin(), data.begin() + Common::Player::bytes()};
    player = deserializePlayer(tmp);
    
    data.erase(data.begin(), data.begin() + Common::Player::bytes());
    size -= Common::Player::bytes();
    
    return *this;
}

Packet& Packet::operator>>(Common::PlayerControl& playerControl) {
    assert(type == PacketType::PLAYER_CONTROL);
    assert(size > 0);
    
    const std::vector<u8> tmp{data.begin(), data.begin() + Common::PlayerControl::bytes()};
    playerControl = deserializePlayerControl(tmp);
    
    data.erase(data.begin(), data.begin() + Common::PlayerControl::bytes());
    size -= Common::PlayerControl::bytes();
    
    return *this;
}

void broadcastPacket(Packet& packet, ENetHost* host) {
    enet_host_broadcast(host, 0, packet.toENet());
    packet.status = PacketStatus::SENT;
}

void sendPacket(Packet& packet, ENetPeer* peer) {
    enet_peer_send(peer, 0, packet.toENet());
    packet.status = PacketStatus::SENT;
}

}
