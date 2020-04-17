#pragma once

namespace Client {

// Current state of a client's keyboard.
struct KeyboardState {
    bool FORWARD;
    bool BACK;
    bool LEFT;
    bool RIGHT;
    
    KeyboardState();
};

}
