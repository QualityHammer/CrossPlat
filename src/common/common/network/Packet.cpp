#include "Packet.hpp"

#include <cassert>

#include "Serialize.hpp"
#include "Deserialize.hpp"

namespace Net {

Packet::Packet() : status{PacketStatus::IDLE}, type{PacketType::NONE}, size{0}, data{} {}

Packet& Packet::operator<<(const Common::Entity& entity) {
    assert(type == PacketType::ENTITY || type == PacketType::NONE);
    if (type == PacketType::NONE) {
        type = PacketType::ENTITY;
    }
    
    const std::vector<u8> serialized{serialize(entity)};
    data.insert(data.end(), serialized.begin(), serialized.end());
    
    size += entity.bytes();
    
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
    
    size += player.bytes();
    
    return *this;
}

Packet& Packet::operator<<(const Common::PlayerControl& playerControl) {
    assert(type == PacketType::PLAYER_CONTROL || type == PacketType::NONE);
    if (type == PacketType::NONE) {
        type = PacketType::PLAYER_CONTROL;
    }
    
    const std::vector<u8> serialized{serialize(playerControl)};
    data.insert(data.end(), serialized.begin(), serialized.end());
    
    size += playerControl.bytes();
    
    return *this;
}

Packet& Packet::operator>>(Common::Entity &entity) {
    assert(type == PacketType::ENTITY);
    assert(size > 0);
    
    const std::vector<u8> tmp{data.begin(), data.begin() + entity.bytes()};
    entity = deserializeEntity(tmp);
    
    data.erase(data.begin(), data.begin() + entity.bytes());
    size -= entity.bytes();
    
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
    
    const std::vector<u8> tmp{data.begin(), data.begin() + player.bytes()};
    player = deserializePlayer(tmp);
    
    data.erase(data.begin(), data.begin() + player.bytes());
    size -= player.bytes();
    
    return *this;
}

Packet& Packet::operator>>(Common::PlayerControl& playerControl) {
    assert(type == PacketType::PLAYER_CONTROL);
    assert(size > 0);
    
    const std::vector<u8> tmp{data.begin(), data.begin() + playerControl.bytes()};
    playerControl = deserializePlayerControl(tmp);
    
    data.erase(data.begin(), data.begin() + playerControl.bytes());
    size -= playerControl.bytes();
    
    return *this;
}

void readENetPacket(ENetPacket* enetPacket, u8& command, Packet& packet) {
    packet = Packet{};
    const u8* recv{reinterpret_cast<const u8*>(enetPacket->data)};
    command = *recv;
    packet.type = static_cast<PacketType>(*(recv + 1));
    packet.size = *(recv + 2) | (*(recv + 3) << 8);
    const u8 dataOffset{4};
    for (u16 i{dataOffset}; i < packet.size + dataOffset; ++i)
        packet.data.push_back(*(recv + i));
    enet_packet_destroy(enetPacket);
    packet.status = PacketStatus::RECIEVED;
}

ENetPacket* createENetPacket(const u8 command, Packet& packet) {
    std::vector<u8> tmp{{command, static_cast<u8>(packet.type), static_cast<u8>(packet.size & 0xff),
        static_cast<u8>((packet.size & 0xff00) >> 8)}};
    tmp.insert(tmp.end(), packet.data.begin(), packet.data.end());
    return enet_packet_create(tmp.data(), tmp.size(), ENET_PACKET_FLAG_RELIABLE);
}

void broadcastPacket(const u8 command, Packet& packet, ENetHost* host) {
    enet_host_broadcast(host, 0, createENetPacket(command, packet));
    packet.status = PacketStatus::SENT;
}

void sendPacket(const u8 command, Packet& packet, ENetPeer* peer) {
    enet_peer_send(peer, 0, createENetPacket(command, packet));
    packet.status = PacketStatus::SENT;
}

}
