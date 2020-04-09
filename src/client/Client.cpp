#include "Client.h"

#include "render/Pixels.h"
#include <common/PlayerControl.h>

namespace Client {

ClientEngine::ClientEngine()
: m_status{ClientStatus::IDLE}, m_window{},
m_gameState{}, m_keyState{},
m_mouseState{} {
    init();
}

void ClientEngine::run() {
    m_status = ClientStatus::GOOD;
    while (m_status == ClientStatus::GOOD) {
        manageInputs(*this);
        draw();
    }
    
}

void ClientEngine::draw() {
    m_window.draw(m_gameState);
}

void ClientEngine::init() {
    m_status = ClientStatus::IDLE;
}

}
