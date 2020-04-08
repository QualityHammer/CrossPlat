#include "Client.h"

#include "RenderTypes.h"

namespace Client {

ClientEngine::ClientEngine()
: m_status{ClientStatus::IDLE}, m_window{},
m_gameState{} {
    init();
}

void ClientEngine::run() {
    bool running{true};
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e) != 0) {
            switch(e.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    break;
                default:
                    break;
            }
        }
        
        m_gameState.player.a += 2 * M_PI / 360;
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
