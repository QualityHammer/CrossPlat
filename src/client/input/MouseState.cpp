#include "MouseState.hpp"

namespace Client {

MouseState::MouseState() : xMov{0} {}

void MouseState::reset() {
    xMov = 0;
}

}
