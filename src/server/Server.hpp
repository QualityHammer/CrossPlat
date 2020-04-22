#pragma once

#include <vector>
#include <unordered_map>

#include <common/network/Net.hpp>
#include <common/network/Packet.hpp>
#include <common/constructs/Entity.hpp>
#include <common/constructs/GameMap.hpp>
#include <common/constructs/Player.hpp>
#include <common/constructs/PlayerControl.hpp>
#include <common/constructs/Types.hpp>
#include <common/network/NetworkCommands.hpp>

namespace Server {

// Status of the server
enum class ServerStatus {
    IDLE,
    RUNNING,
    EXIT,
    ERROR
};

// This contains everything needed to run a game server
//
// The server can connect to clients to share gamestates
// and achieve multiplayer.
class ServerEngine {
public:
    // Initialize server
    ServerEngine();
    // Destroy server
    ~ServerEngine();
    
    // The max number of clients allowed to connect.
    const u8 maxConnections;
    // Current status
    ServerStatus status;
    
    // Loop used to run a server.
    void run();
private:
    // ENet server host
    ENetHost* m_server;
    // ENet server address
    ENetAddress m_address;
    // All of the currently connected client's address numbers.
    std::unordered_map<ENetPeer*, u8> m_clients;
    std::vector<bool> m_availID;
    std::unordered_map<u8, Common::Player> m_players;
    std::vector<Common::Entity> m_entities;
    
    const Common::GameMap m_gameMap;
    
    // Sends a packet to all clients currently connected.
    void broadcastClientPacket(const Net::ServerCommand command, Net::Packet& packet) const;
    // Callback to recieve a packet from a client.
    void recievePacket(ENetEvent& event);
    // Sends a packet to a single client.
    void sendClientPacket(const Net::ServerCommand command, Net::Packet& packet, ENetPeer* peer) const;
    
    // Callback for when a client connects.
    void newClientConnection(ENetEvent& event);
    // Callback for when a client disconnects.
    void removeClientConnection(ENetEvent& event);
};

}
