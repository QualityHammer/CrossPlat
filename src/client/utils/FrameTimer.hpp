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
        u32 m_frameStart;
        u32 m_frameEnd;
        u16 m_deltaTime;
        u16 m_avgDeltaTime;
};

}
