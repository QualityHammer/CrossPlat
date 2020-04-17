#pragma once

#include "render/sdl/Window.hpp"
#include "input/MouseState.hpp"
#include "input/KeyboardState.hpp"
#include "GameState.hpp"

namespace Client {

// The stauts of the client program
enum class ClientStatus {
    GOOD,
    IDLE,
    EXIT,
    FAILED
};

// Contains everything needed for a client to run a game.
class ClientEngine {
public:
    // Initialize client
    ClientEngine();
    
    // Draw pixels to screen based on current game state.
    void draw();
    // Main client loop to run the game.
    void run();
private:
    // Current status
    ClientStatus m_status;
    // SDL window
    Window m_window;
    // Current game state
    GameState m_gameState;
    // Current keyboard state
    KeyboardState m_keyState;
    // Current mouse state
    MouseState m_mouseState;
    
    void init();
    // A function used to check for inputs
    friend void manageInputs(ClientEngine& client);
};

}
