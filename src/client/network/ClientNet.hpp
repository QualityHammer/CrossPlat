#pragma once

#include "../GameState.hpp"
#include <common/network/Net.hpp>

namespace Client {

class ClientNet {
public:
    ClientNet(GameState& gameState);
    ~ClientNet();
    
    void connect();
    void disconnect();
    void getUpdates();
    void recievePacket(ENetEvent& event);
private:
    ENetHost* m_client;
    ENetAddress m_address;
    ENetPeer* m_server;
    GameState& m_gameState;
};

}
