#include "MouseState.h"

namespace Client {

MouseState::MouseState() : xMov{0} {}

void MouseState::reset() {
    xMov = 0;
}

}
