#include "Client.hpp"

#include "render/Pixels.hpp"
#include <common/constructs/PlayerControl.hpp>

namespace Client {

ClientEngine::ClientEngine()
: m_status{ClientStatus::IDLE}, m_window{},
m_gameState{}, m_keyState{},
m_mouseState{}, m_network{m_gameState} {
    init();
}

void ClientEngine::run() {
    m_status = ClientStatus::GOOD;
    m_network.connect();
    while (m_status == ClientStatus::GOOD) {
        m_network.getUpdates();
        manageInputs(*this);
        draw();
    }
    m_network.disconnect();
}

void ClientEngine::draw() {
    m_window.draw(m_gameState);
}

void ClientEngine::init() {
    m_status = ClientStatus::IDLE;
}

}
