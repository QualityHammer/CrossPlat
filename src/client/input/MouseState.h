#pragma once

#include <common/constructs/Types.h>

namespace Client {

struct MouseState {
    i16 xMov;
    
    MouseState();
    void reset();
};

}
