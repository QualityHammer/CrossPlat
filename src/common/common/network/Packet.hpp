#pragma once

#include <vector>

#include "Net.hpp"
#include "../constructs/Types.hpp"

namespace Net {

// Current status of a packet
enum class PacketStatus {
    IDLE,
    SENT,
    RECIEVED
};

// Type of data contained in a packet
enum class PacketType : u8 {
    NONE,
    GAME_MAP,
    ENTITY,
    PLAYER,
    PLAYER_CONTROL
};

// Represents an ENet packet along with
// all the data needed to determine what is in the packet.
class Packet {
public:
    // Initializes packet data
    Packet();
    
    // Current status
    PacketStatus status;
    // Packet type
    PacketType type;
    // Size of packet in bytes
    // (does not include the 3 bytes of data used
    //  to contain the packet type and size)
    u16 size;
    // Packet data in bytes
    std::vector<u8> data;
};

void readENetPacket(ENetPacket* enetPacket, u8& command, Packet& packet);
ENetPacket* createENetPacket(const u8 command, Packet& packet);
// Sends a packet to all peers connected to the host
void broadcastPacket(const u8 command, Packet& packet, ENetHost* host);
// Sends a packet to a peer.
void sendPacket(const u8 command, Packet& packet, ENetPeer* peer);

}
