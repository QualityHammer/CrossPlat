#include "Server.hpp"

#include <algorithm>

#include <common/constructs/Entity.hpp>
#include <common/Debug.hpp>
#include <common/network/NetworkErrors.hpp>

namespace Server {

ServerEngine::ServerEngine() : maxConnections{5}, status{ServerStatus::IDLE}, m_server{nullptr} {
    m_address.host = ENET_HOST_ANY;
    m_address.port = 1513;
    m_server = enet_host_create(&m_address, maxConnections, 2, 0, 0);
    if (m_server == nullptr) {
        ServerError(ServerErrorType::INIT_FAILED);
        exit(1);
    }
    Debug::serverRunning("localhost", m_address.port);
    m_clients.reserve(maxConnections);
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
    m_clients.push_back(event.peer);
    Net::Packet packet{};
    Common::Entity entity{13.53, 2.456, 1, 29, 0};
    packet << entity;
    sendClientPacket(packet, event.peer);
}

void ServerEngine::recievePacket(ENetEvent &event) {
    Debug::clientPacketRecieved();
}

void ServerEngine::removeClientConnection(ENetEvent &event) {
    Debug::clientDisconnected();
    m_clients.erase(std::find(m_clients.begin(), m_clients.end(), event.peer));
}

void ServerEngine::sendClientPacket(Net::Packet& packet, ENetPeer* peer) const {
    sendPacket(packet, peer);
    enet_host_flush(m_server);
}

void ServerEngine::run() {
    status = ServerStatus::RUNNING;
    while (status == ServerStatus::RUNNING) {
        ENetEvent event;
        while (enet_host_service(m_server, &event, 1000) > 0) {
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
        Net::Packet packet{};
        Common::Entity entity{13.53, 2.456, 1, 29, 0};
        packet << entity;
        broadcastClientPacket(packet);
    }
}

}
