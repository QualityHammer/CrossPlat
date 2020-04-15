#pragma once

#include "render/sdl/Window.hpp"
#include "input/MouseState.hpp"
#include "input/KeyboardState.hpp"
#include "GameState.hpp"

namespace Client {

enum class ClientStatus {
    GOOD,
    IDLE,
    EXIT,
    FAILED
};

class ClientEngine {
public:
    ClientEngine();
    
    void draw();
    void run();
private:
    ClientStatus m_status;
    Window m_window;
    GameState m_gameState;
    KeyboardState m_keyState;
    MouseState m_mouseState;
    
    void init();
    friend void manageInputs(ClientEngine& client);
};

}
