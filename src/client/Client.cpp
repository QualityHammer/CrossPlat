#include "Client.hpp"

#include <cmath>

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
        if (m_keyState.FORWARD || m_keyState.BACK) {
            Common::PlayerControl pc{0, 0, 0};
            pc.moveX += (m_keyState.FORWARD + -m_keyState.BACK) *
                std::cos(m_gameState.player.a) * 100;
            pc.moveY += (m_keyState.FORWARD + -m_keyState.BACK) *
                std::sin(m_gameState.player.a) * 100;
            m_network.sendPlayerControl(pc);
        }
        
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
