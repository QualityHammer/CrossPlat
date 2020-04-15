#pragma once

#include <vector>

#include <common/network/Net.hpp>
#include <common/constructs/Types.hpp>

namespace Server {

class ServerEngine {
public:
    ServerEngine();
    ~ServerEngine();
    
    const u8 maxConnections;
    
    void run();
private:
    ENetHost* m_server;
    ENetAddress m_address;
    std::vector<u32> m_clients;
    
//    void broadcastClientPacket(Packet& packet) const;
    void recievePacket(ENetEvent& event);
//    void sendClientPacket(Packet& packet, ENetPeer* peer) const;
    
    void newClientConnection(ENetEvent& event);
    void removeClientConnection(ENetEvent& event);
};

}
