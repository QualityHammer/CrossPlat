#include <SDL.h>
#include <cmath>

#include "../Client.hpp"

namespace Client {

void keyChanged(const SDL_Keycode keycode, KeyboardState& keyState, const bool pressed) {
    switch (keycode) {
        case SDLK_w:
            keyState.FORWARD = pressed;
            break;
        case SDLK_s:
            keyState.BACK = pressed;
            break;
        case SDLK_a:
            keyState.LEFT = pressed;
            break;
        case SDLK_d:
            keyState.RIGHT = pressed;
            break;
        default: break;
    }
}

void checkQuit(const SDL_Event& e, ClientStatus& status) {
    switch (e.type) {
        case SDL_QUIT:
            status = ClientStatus::EXIT;
            break;
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    status = ClientStatus::EXIT;
                    break;
                default: break;
            }
            break;
        default: break;
    }
}

void manageInputs(ClientEngine& client) {
    SDL_Event e;
    client.m_mouseState.reset();
    while (SDL_PollEvent(&e) != 0) {
        const auto keycode{e.key.keysym.sym};
        checkQuit(e, client.m_status);
        switch(e.type) {
            case SDL_KEYDOWN:
                keyChanged(keycode, client.m_keyState, true);
                break;
            case SDL_KEYUP:
            keyChanged(keycode, client.m_keyState, false);
                break;
            case SDL_MOUSEMOTION:
                client.m_mouseState.xMov = e.motion.xrel;
                break;
            default: break;
        }
    }
    
    // Move to server
    //
    // Move view (look around)
    client.m_gameState.player.a += (float)client.m_mouseState.xMov * 0.01;
    
    // Move position
    client.m_gameState.player.x += (client.m_keyState.FORWARD + -client.m_keyState.BACK) *
    std::cos(client.m_gameState.player.a) * 0.1f;
    client.m_gameState.player.y += (client.m_keyState.FORWARD + -client.m_keyState.BACK) *
    std::sin(client.m_gameState.player.a) * 0.1f;
}

}
