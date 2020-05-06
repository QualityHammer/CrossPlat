#pragma once

#include "../GameState.hpp"
#include <common/network/Net.hpp>
#include <common/network/NetworkCommands.hpp>
#include <common/constructs/Player.hpp>

namespace Client {

class ClientNet {
public:
    ClientNet(GameState& gameState);
    ~ClientNet();
    
    void connect();
    void disconnect();
    void getUpdates();
    void sendPlayerPos(Common::Player& player);
    void recievePacket(ENetEvent& event);
private:
    ENetHost* m_client;
    ENetAddress m_address;
    ENetPeer* m_server;
    GameState& m_gameState;
    u8 PID;

    u8 m_playerCountdown;
};

}
