#include <common/constructs/Types.hpp>

namespace Client {

class FrameTimer {
    public:
        FrameTimer();

        void pauseFrame();
        void start();
        void stop();
    private:
        u32 m_frameStart;
        u32 m_frameEnd;
        u16 m_deltaTime;
        const u16 m_avgDeltaTime;
};

}
