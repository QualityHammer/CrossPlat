#pragma once

namespace Client {

// Current state of a client's keyboard.
struct KeyboardState {
    // Movement
    bool FORWARD;
    bool BACK;
    bool LEFT;
    bool RIGHT;
    
    // Client options
    bool K_P;
    
    KeyboardState();
};

}
