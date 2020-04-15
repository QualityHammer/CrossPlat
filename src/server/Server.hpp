#pragma once

#include <vector>

#include <common/network/Net.hpp>
#include <common/network/Packet.hpp>
#include <common/constructs/Types.hpp>

namespace Server {

enum class ServerStatus {
    IDLE,
    RUNNING,
    EXIT,
    ERROR
};

class ServerEngine {
public:
    ServerEngine();
    ~ServerEngine();
    
    const u8 maxConnections;
    ServerStatus status;
    
    void run();
private:
    ENetHost* m_server;
    ENetAddress m_address;
    std::vector<u32> m_clients;
    
    void broadcastClientPacket(Net::Packet& packet) const;
    void recievePacket(ENetEvent& event);
    void sendClientPacket(Net::Packet& packet, ENetPeer* peer) const;
    
    void newClientConnection(ENetEvent& event);
    void removeClientConnection(ENetEvent& event);
};

}
