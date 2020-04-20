#include "FrameTimer.hpp"

#include "../ClientOptions.hpp"

namespace Client {

    FrameTimer::FrameTimer() : m_frameStart{0}, m_frameEnd{0}, m_deltaTime{0}, 
        m_avgDeltaTime{1000 / FPS} {}

    void FrameTimer::pause() {}

    void FrameTimer::start() {}

    void FrameTimer::stop() {}

    void FrameTimer::unpause() {}

}
