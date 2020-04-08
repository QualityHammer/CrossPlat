#pragma once

#include "Window.h"
#include "RenderTypes.h"
#include "GameState.h"

namespace Client {

enum class ClientStatus {
    GOOD,
    IDLE,
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
    
    void init();
};

}
