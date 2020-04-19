#pragma once

#include <vector>

#include "Net.hpp"
#include "../constructs/Entity.hpp"
#include "../constructs/GameMap.hpp"
#include "../constructs/Player.hpp"
#include "../constructs/PlayerControl.hpp"
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
    
    // Creates and returns a ENet packet from the
    // data in this packet.
    ENetPacket* toENet() const;
    
    // Initializes data in this packet from the ENet packet.
    Packet& operator<<(ENetPacket* enetPacket);
    
    Packet& operator<<(const Common::Entity& entity);
    Packet& operator>>(Common::Entity& entity);
    Packet& operator<<(const Common::GameMap& gameMap);
    Packet& operator>>(Common::GameMap& gameMap);
    Packet& operator<<(const Common::Player& player);
    Packet& operator>>(Common::Player& player);
    Packet& operator<<(const Common::PlayerControl& playerControl);
    Packet& operator>>(Common::PlayerControl& playerControl);
};

// Sends a packet to all peers connected to the host
void broadcastPacket(Packet& packet, ENetHost* host);
// Sends a packet to a peer.
void sendPacket(Packet& packet, ENetPeer* peer);

}
