#include "Server.hpp"

#include <iostream>

#include <common/network/NetworkErrors.hpp>

namespace Server {

ServerEngine::ServerEngine() : maxConnections{5}, m_server{nullptr} {
    m_address.host = ENET_HOST_ANY;
    m_address.port = 1513;
    m_server = enet_host_create(&m_address, maxConnections, 2, 0, 0);
    if (m_server == nullptr) {
        ServerError(ServerErrorType::INIT_FAILED);
        exit(1);
    }
    std::cout << "Server running on localhost:" << m_address.port << std::endl;
    m_clients.reserve(maxConnections);
}

}
