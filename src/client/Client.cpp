#include "Client.h"

#include <cmath>

#include "render/Pixels.h"
#include <common/PlayerControl.h>

namespace Client {

ClientEngine::ClientEngine()
: m_status{ClientStatus::IDLE}, m_window{},
m_gameState{}, m_keyState{false, false, false, false},
m_mouseState{0} {
    init();
}

void ClientEngine::run() {
    bool running{true};
    SDL_Event e;
    while (running) {
        m_mouseState.reset();
        while (SDL_PollEvent(&e) != 0) {
            const auto keycode{e.key.keysym.sym};
            switch(e.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch (keycode) {
                        case SDLK_w:
                            m_keyState.FORWARD = true;
                            break;
                        case SDLK_s:
                            m_keyState.BACK = true;
                            break;
                        case SDLK_a:
                            m_keyState.LEFT = true;
                            break;
                        case SDLK_d:
                            m_keyState.RIGHT = true;
                            break;
                        default: break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (keycode) {
                        case SDLK_w:
                            m_keyState.FORWARD = false;
                            break;
                        case SDLK_s:
                            m_keyState.BACK = false;
                            break;
                        case SDLK_a:
                            m_keyState.LEFT = false;
                            break;
                        case SDLK_d:
                            m_keyState.RIGHT = false;
                            break;
                        default: break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    m_mouseState.xMov = e.motion.xrel;
                    break;
                default: break;
            }
        }
        
        // Move to server
        m_gameState.player.a += (float)m_mouseState.xMov * 0.01;
        
        m_gameState.player.x += (m_keyState.FORWARD + -m_keyState.BACK) *
        std::cos(m_gameState.player.a) * 0.1f;
        m_gameState.player.y += (m_keyState.FORWARD + -m_keyState.BACK) *
        std::sin(m_gameState.player.a) * 0.1f;
        
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
