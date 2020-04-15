#pragma once

#include <common/constructs/Types.hpp>

namespace Client {

struct MouseState {
    i16 xMov;
    
    MouseState();
    void reset();
};

}
