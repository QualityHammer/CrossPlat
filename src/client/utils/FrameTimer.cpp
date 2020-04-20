#include "FrameTimer.hpp"

#include "SDL.h"

#include "../ClientOptions.hpp"
#include <common/Debug.hpp>

namespace Client {

    FrameTimer::FrameTimer() : m_timerRunning{false}, m_timerPaused{false}, m_frameStart{0}, 
        m_frameEnd{0}, m_deltaTime{0}, m_avgDeltaTime{1000 / FPS} {}

    void FrameTimer::pause() {
        if (m_timerRunning && !m_timerPaused) {
            m_timerPaused = true;
            m_frameEnd = SDL_GetTicks();
            m_deltaTime = m_frameEnd - m_frameStart;
            Debug::showFrameTime(m_deltaTime);
            if (m_deltaTime < m_avgDeltaTime)
                SDL_Delay(m_avgDeltaTime - m_deltaTime);
        }
    }

    void FrameTimer::start() {
        if (!m_timerRunning) {
            m_timerRunning = true;
            m_frameStart = SDL_GetTicks();
            m_frameEnd = 0;
            m_deltaTime = 0;
        }
    }

    void FrameTimer::stop() {
        if (m_timerRunning) {
            m_timerRunning = false;
            m_frameStart = 0;
            m_frameEnd = 0;
            m_deltaTime = 0;
        }
    }
    
    void FrameTimer::unpause() {
        if (m_timerRunning && m_timerPaused) {
            m_timerPaused = false;
            m_frameStart = SDL_GetTicks();
            m_frameEnd = 0;
        }
    }

}
