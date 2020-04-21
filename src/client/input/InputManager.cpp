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
        case SDLK_p:
            keyState.K_P = pressed;
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
}

}
