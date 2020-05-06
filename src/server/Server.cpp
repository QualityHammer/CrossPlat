#include "Server.hpp"

#include <iostream>
#include <algorithm>
#include <unistd.h>

#include <common/constructs/Entity.hpp>
#include <common/Debug.hpp>
#include <common/network/NetworkErrors.hpp>

namespace Server {

ServerEngine::ServerEngine() : maxConnections{5}, status{ServerStatus::IDLE}, m_server{nullptr},
m_availID{}, m_players{}, m_entities{{
  {5.234f, 5.234f, 0.0f, 0.0f, 29},
  {2.234f, 13.234f, 0.0f, 0.0f, 30},
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
    1,  0,  0,  0,  0,  0, 21, 22, 23,  0,  0,  0,  0,  0,  0,  1,
    1,  0,  0,  0,  0,  0,  0,  0,  0, 17,  0,  0,  0,  0,  0,  1,
    1,  0,  0,  0,  0, 24,  0,  0,  0, 18,  0,  0,  0,  0,  0,  1,
    1,  0,  0,  0,  0, 25,  0,  0,  0, 19,  0, 13, 14, 15, 16,  1,
    1,  0,  0,  0,  0, 26,  0,  0,  0, 20, 12,  0,  0,  0,  0,  1,
    1,  0,  0,  0,  0, 27,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,
    1,  0,  0,  0,  0,  0, 28,  0, 29, 10, 10,  0,  0,  0,  0,  3,
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
}

ServerEngine::~ServerEngine() {
  enet_host_destroy(m_server);
}

void ServerEngine::broadcastClientPacket(const Net::ServerCommand command, Net::Packet& packet) const {
  Net::broadcastPacket(static_cast<u8>(command), packet, m_server);
  enet_host_flush(m_server);
}

void ServerEngine::newClientConnection(ENetEvent &event) {
  Debug::clientConnected();
  Net::Packet gmPack{};
  Net::Packet ePack{};
  Net::Packet pPack{};
  // Create PID
  for (u8 i{0}; i < m_availID.size() - 1; ++i) {
    if (!m_availID[i]) {
      m_availID[i] = true;
      m_players[i] = {{3.234f, 3.234f, 0.0f, 0.0f, 30}, 1.4f, i};
      m_clients[event.peer] = i;
      event.peer->data = &m_clients[event.peer];
      break;
    }
  }
  // Send game map
  gmPack << m_gameMap;
  sendClientPacket(Net::ServerCommand::GAME_MAP, gmPack, event.peer);
  // Send entities
  for (const auto& entity : m_entities) {
    ePack << entity;
  }
  sendClientPacket(Net::ServerCommand::ENTITY, ePack, event.peer);
  // Send client's player for initialization
  Net::Packet eUpdate{};
  eUpdate << m_players[m_clients[event.peer]];
  sendClientPacket(Net::ServerCommand::CLIENT_PLAYER, eUpdate, event.peer);
  // Send existing players
  for (const auto& pair : m_players) {
    if (pair.first != m_clients[event.peer])
      pPack << pair.second;
  }
  sendClientPacket(Net::ServerCommand::PLAYER, pPack, event.peer);
  // Broadcast client's player to all clients
  broadcastClientPacket(Net::ServerCommand::PLAYER, eUpdate);
}

void ServerEngine::recievePacket(ENetEvent &event) {
  Debug::clientPacketRecieved();
  Net::Packet packet;
  Net::ClientCommand command;
  Net::readENetPacket(event.packet, reinterpret_cast<u8&>(command), packet);
  if (command == Net::ClientCommand::PLAYER) {
    packet >> m_players[m_clients[event.peer]];
    m_players[m_clients[event.peer]].x += m_players[m_clients[event.peer]].velX;
    m_players[m_clients[event.peer]].y += m_players[m_clients[event.peer]].velY;
    Net::Packet playerPack{};
    playerPack << m_players[m_clients[event.peer]];
    broadcastClientPacket(Net::ServerCommand::PLAYER, playerPack);
  }
}

void ServerEngine::removeClientConnection(ENetEvent &event) {
  Debug::clientDisconnected();
  Net::Packet pPack{};
  pPack << m_players[m_clients[event.peer]];
  broadcastClientPacket(Net::ServerCommand::PLAYER_EXIT, pPack);
  m_players.erase(m_clients[event.peer]);
  m_availID[m_clients[event.peer]] = false;
  m_clients.erase(event.peer);
  event.peer->data = NULL;
}

void ServerEngine::sendClientPacket(const Net::ServerCommand command, Net::Packet& packet, ENetPeer* peer) const {
  sendPacket(static_cast<u8>(command), packet, peer);
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
