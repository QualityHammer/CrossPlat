#include <common/constructs/Types.hpp>

namespace Client {

class FrameTimer {
    public:
        FrameTimer();

        void pause();
        void start();
        void stop();
        void unpause();
    private:
        bool m_timerRunning;
        bool m_timerPaused;
        u32 m_frameStart;
        u32 m_frameEnd;
        u16 m_deltaTime;
        const u16 m_avgDeltaTime;
};

}
