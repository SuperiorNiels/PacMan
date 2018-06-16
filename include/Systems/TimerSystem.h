//
// Created by niels on 08/03/18.
//

#ifndef ECS_TIMERSYSTEM_H
#define ECS_TIMERSYSTEM_H

#include "../ECS/ECS.h"

using namespace ECS;

namespace Systems {
    class TimerSystem {
    public:
        TimerSystem() {
            SCREEN_FPS = 60;
            SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
        };

        explicit TimerSystem(int fps) {
            SCREEN_FPS = fps;
            SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
        };

        virtual void fpsStart() = 0;

        virtual void fpsCap() = 0;

        virtual void startTimer() = 0;

        virtual unsigned int getTime() = 0;

        virtual void resetTimer() = 0;

        virtual unsigned int getTimerStep() = 0;

        virtual unsigned int getTimerAndReset() = 0;

        int getFPS() { return SCREEN_FPS; };

        int getTickPerFrame() { return SCREEN_TICKS_PER_FRAME; };
    protected:
        int SCREEN_FPS = 0;
        int SCREEN_TICKS_PER_FRAME = 0;
    };
};


#endif //ECS_TIMERSYSTEM_H
