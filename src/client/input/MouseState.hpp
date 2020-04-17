#pragma once

#include <common/constructs/Types.hpp>

namespace Client {

// Current state of a client's mouse
struct MouseState {
    i16 xMov;
    
    MouseState();
    void reset();
};

}
