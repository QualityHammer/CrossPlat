#include "Server.hpp"

#include <algorithm>
#include <unistd.h>

#include <common/constructs/Entity.hpp>
#include <common/Debug.hpp>
#include <common/network/NetworkErrors.hpp>

namespace Server {

ServerEngine::ServerEngine() : maxConnections{5}, status{ServerStatus::IDLE}, m_server{nullptr},
m_availID{}, m_entities{{
    {0, {5.234, 5.234, 0, 29, 0}},
    {1, {2.234, 13.234, 0, 30, 1}},
}}, m_gameMap {
    16,
    16,
    16 * 16,
    {
          1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
          1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
          1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
          1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
          1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
          1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
          1,  0,  0,  0,  0,  0, 18, 19, 20,  0,  0,  0,  0,  0,  0,  1,
          1,  0,  0,  0,  0,  0,  0,  0,  0, 27,  0,  0,  0,  0,  0,  1,
          1,  0,  0,  0,  0, 21,  0,  0,  0, 28,  0,  0,  0,  0,  0,  1,
          1,  0,  0,  0,  0, 22,  0,  0,  0, 29,  0, 13, 14, 15, 16,  1,
          1,  0,  0,  0,  0, 23,  0,  0,  0, 17, 12,  0,  0,  0,  0,  1,
          1,  0,  0,  0,  0, 24,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,
          1,  0,  0,  0,  0,  0, 25,  0, 26, 10, 10,  0,  0,  0,  0,  3,
          1,  0,  0,  0,  0,  0,  0,  0,  0, 11, 11,  0,  0,  0,  0,  4,
          1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,
          1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  5,  6,  7,  8,  9,  1
    },
} {
    m_address.host = ENET_HOST_ANY;
    m_address.port = 1513;
    m_server = enet_host_create(&m_address, maxConnections, 2, 0, 0);
    if (m_server == nullptr) {
        ServerError(ServerErrorType::INIT_FAILED);
        exit(1);
    }
    Debug::serverRunning("localhost", m_address.port);
    m_availID.resize(255);
    m_availID[0] = true;
    m_availID[1] = true;
}

ServerEngine::~ServerEngine() {
    enet_host_destroy(m_server);
}

void ServerEngine::broadcastClientPacket(Net::Packet& packet) const {
    Net::broadcastPacket(packet, m_server);
    enet_host_flush(m_server);
}

void ServerEngine::newClientConnection(ENetEvent &event) {
    Debug::clientConnected();
    Net::Packet gmPack{};
    Net::Packet ePack{};
    for (u8 i{0}; i < m_availID.size() - 1; ++i) {
        if (!m_availID[i]) {
            m_availID[i] = true;
            m_entities[i] = {3.234, 3.234, 1, 29, i};
            m_clients[event.peer] = i;
            event.peer->data = &m_clients[event.peer];
            break;
        }
    }
    gmPack << m_gameMap;
    sendClientPacket(gmPack, event.peer);
    for (auto it{m_entities.rbegin()}; it != m_entities.rend(); ++it) {
        ePack << it->second;
    }
    sendClientPacket(ePack, event.peer);
    Net::Packet eUpdate{};
    eUpdate << m_entities[m_clients[event.peer]];
    broadcastClientPacket(eUpdate);
}

void ServerEngine::recievePacket(ENetEvent &event) {
    Debug::clientPacketRecieved();
    Net::Packet packet{};
    packet << event.packet;
    if (packet.type == Net::PacketType::PLAYER_CONTROL) {
        Common::PlayerControl pc;
        packet >> pc;
        Common::Entity& player{m_entities[m_clients[event.peer]]};
        player.x += pc.moveX * 0.001f;
        player.y += pc.moveY * 0.001f;
        Net::Packet entPack{};
        entPack << player;
        broadcastClientPacket(entPack);
    }
}

void ServerEngine::removeClientConnection(ENetEvent &event) {
    Debug::clientDisconnected();
    m_entities.erase(m_clients[event.peer]);
    m_availID[m_clients[event.peer]] = false;
    m_clients.erase(event.peer);
    event.peer->data = NULL;
}

void ServerEngine::sendClientPacket(Net::Packet& packet, ENetPeer* peer) const {
    sendPacket(packet, peer);
    enet_host_flush(m_server);
}

void ServerEngine::run() {
    status = ServerStatus::RUNNING;
    while (status == ServerStatus::RUNNING) {
        ENetEvent event;
        while (enet_host_service(m_server, &event, 0) > 0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_CONNECT:
                    newClientConnection(event);
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    removeClientConnection(event);
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    recievePacket(event);
                    break;
                default: break;
            }
        }
        usleep(20);
    }
}

}
