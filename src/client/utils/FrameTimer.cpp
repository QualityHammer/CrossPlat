#include "FrameTimer.hpp"

#include "SDL.h"
#include <iostream>

#include "../ClientOptions.hpp"

namespace Client {

    FrameTimer::FrameTimer() : m_frameStart{0}, m_frameEnd{0}, m_deltaTime{0}, 
        m_avgDeltaTime{1000 / FPS} {}

    void FrameTimer::pauseFrame() {
        m_frameEnd = SDL_GetTicks();
        m_deltaTime = m_frameEnd - m_frameStart;
        if (m_deltaTime < m_avgDeltaTime)
            SDL_Delay(m_avgDeltaTime - m_deltaTime);
        m_frameStart = SDL_GetTicks();
        m_frameEnd = 0;
    }

    void FrameTimer::start() {
        m_frameStart = SDL_GetTicks();
        m_frameEnd = 0;
        m_deltaTime = 0;
    }

    void FrameTimer::stop() {
        m_frameStart = 0;
        m_frameEnd = 0;
        m_deltaTime = 0;
    }

}
