#pragma once

#include <vector>

#include "Net.hpp"
#include "../constructs/Types.hpp"

namespace Net {

enum class PacketStatus {
    IDLE,
    SENT,
    RECIEVED
};

enum class PacketType : u8 {
    NONE,
    GAME_MAP,
    ENTITY,
    PLAYER_CONTROL
};

class Packet {
public:
    Packet();
    
    PacketStatus status;
    PacketType type;
    u16 size;
    std::vector<u8> data;
    
    ENetPacket* toENet() const;
    
    Packet& operator<<(ENetPacket* enetPacket);
};

void broadcastPacket(Packet& packet, ENetHost* host);
void sendPacket(Packet& packet, ENetPeer* peer);

}
