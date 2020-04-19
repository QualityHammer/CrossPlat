#include "ClientNet.hpp"

#include <common/network/Packet.hpp>
#include <common/network/NetworkErrors.hpp>
#include <common/Debug.hpp>

namespace Client {

ClientNet::ClientNet(GameState& gameState) : m_client{nullptr}, m_server{nullptr}, m_gameState{gameState}, EID{0} {
    m_client = enet_host_create(NULL, 1, 2, 0, 0);
    if (m_client == nullptr) {
        ClientError(ClientErrorType::INIT_FAILED);
        return;
    }
    
    enet_address_set_host(&m_address, "localhost");
    m_address.port = 1513;
}

ClientNet::~ClientNet() {
    enet_host_destroy(m_client);
}

void ClientNet::connect() {
    m_server = enet_host_connect(m_client, &m_address, 2, 0);
    if (m_server == nullptr) {
        ClientError(ClientErrorType::NO_SERVER_FOUND);
        return;
    }
    
    ENetEvent event;
    if (enet_host_service(m_client, &event, 5000) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT) {
        Debug::serverConnected("localhost");
    } else {
        enet_peer_reset(m_server);
        ClientError(ClientErrorType::CONNECTION_FAILED);
        return;
    }
}

void ClientNet::disconnect() {
    ENetEvent event;
    enet_peer_disconnect(m_server, 0);
    while (enet_host_service(m_client, &event, 3000) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_DISCONNECT:
                Debug::serverDisconnected();
                return;
            default: break;
        }
    }
    enet_peer_reset(m_server);
}

void ClientNet::getUpdates() {
    ENetEvent event;
    while (enet_host_service(m_client, &event, 0) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                recievePacket(event);
                break;
            default: break;
        }
    }
}

void ClientNet::sendPlayerControl(Common::PlayerControl& pc) {
    Net::Packet packet{};
    packet << pc;
    Net::sendPacket(packet, m_server);
    enet_host_flush(m_client);
}

void ClientNet::recievePacket(ENetEvent &event) {
    Net::Packet packet{};
    packet << event.packet;
    Debug::showPacket(packet);
    Common::Entity entity;
    switch (packet.type) {
        case Net::PacketType::GAME_MAP:
            packet >> m_gameState.gMap;
            break;
        case Net::PacketType::ENTITY:
            while (packet.size > 0) {
                packet >> entity;
                if (entity.type == 1 && EID == 0)
                    EID = entity.EID;
                if (entity.type == 1 && entity.EID == EID) {
                    m_gameState.player.x = entity.x;
                    m_gameState.player.y = entity.y;
                } else {
                    m_gameState.entities[entity.EID] = entity;
                }
            }
        default:
            break;
    }
}


}
