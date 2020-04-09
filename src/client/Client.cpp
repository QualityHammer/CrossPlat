#include "Client.h"

#include <cmath>

#include "render/RenderTypes.h"
#include <common/PlayerControl.h>

namespace Client {

ClientEngine::ClientEngine()
: m_status{ClientStatus::IDLE}, m_window{},
m_gameState{} {
    init();
}

void ClientEngine::run() {
    bool running{true};
    SDL_Event e;
    Common::PlayerControl pc{0, 0};
    while (running) {
        while (SDL_PollEvent(&e) != 0) {
            const auto keycode{e.key.keysym.sym};
            switch(e.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch (keycode) {
                        case SDLK_w:
                            pc.move = 1;
                            break;
                        case SDLK_s:
                            pc.move = -1;
                            break;
                        case SDLK_a:
                            pc.turn = -1;
                            break;
                        case SDLK_d:
                            pc.turn = 1;
                            break;
                        default: break;
                    }
                    break;
                case SDL_KEYUP:
                    if (keycode == SDLK_w || keycode == SDLK_s)
                        pc.move = 0;
                    if (keycode == SDLK_a || keycode == SDLK_d)
                        pc.turn = 0;
                    break;
                default: break;
            }
        }
        
        // Move to server
        m_gameState.player.a += (float)pc.turn * 0.05;
        m_gameState.player.x += (float)pc.move *
        std::cos(m_gameState.player.a) * 0.1;
        m_gameState.player.y += (float)pc.move *
        std::sin(m_gameState.player.a) * 0.1;
        
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
