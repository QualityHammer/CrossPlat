#include "Client.hpp"

#include <cmath>

#include "render/Pixels.hpp"
#include <common/constructs/PlayerControl.hpp>

namespace Client {

ClientEngine::ClientEngine() : m_status{ClientStatus::IDLE}, m_window{},
m_gameState{}, m_keyState{}, m_mouseState{}, m_network{m_gameState}, m_frameTimer{},
focusMouse{true} {
    init();
}

void ClientEngine::run() {
    m_status = ClientStatus::GOOD;
    m_network.connect();
    m_frameTimer.start();
    while (m_status == ClientStatus::GOOD) {
        m_network.getUpdates();
        manageInputs(*this);
        update();
        m_frameTimer.unpause();
        draw();
        m_frameTimer.pause();
    }
    m_network.disconnect();
    m_frameTimer.stop();
}

void ClientEngine::draw() {
    m_window.draw(m_gameState);
}

void ClientEngine::init() {
    m_status = ClientStatus::IDLE;
}

void ClientEngine::update() {
    if (m_keyState.FORWARD || m_keyState.BACK || m_mouseState.xMov != 0) {
        Common::PlayerControl pc{0, 0, 0};
        pc.moveX += (m_keyState.FORWARD + -m_keyState.BACK) *
            std::cos(m_gameState.player.a) * 100;
        pc.moveY += (m_keyState.FORWARD + -m_keyState.BACK) *
            std::sin(m_gameState.player.a) * 100;
        pc.turn = (float)m_mouseState.xMov * 0.01;
        m_network.sendPlayerControl(pc);
    }
    if (m_keyState.K_P) {
        m_keyState.K_P = false;
        focusMouse = !focusMouse;
        m_window.setMouseFocus(focusMouse);
    }
}

}
