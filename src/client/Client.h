#pragma once

#include "render/sdl/Window.h"
#include "input/MouseState.h"
#include "input/KeyboardState.h"
#include "GameState.h"

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
