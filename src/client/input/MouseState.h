#pragma once

#include <common/Types.h>

namespace Client {

struct MouseState {
    i16 xMov;
    
    MouseState();
    void reset();
};

}
