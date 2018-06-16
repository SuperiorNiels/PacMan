//
// Created by niels on 08/03/18.
//

#ifndef ECS_SDL_TIMERSYSTEM_H
#define ECS_SDL_TIMERSYSTEM_H


#include <SDL_types.h>
#include <SDL_timer.h>
#include "../Systems/TimerSystem.h"

using namespace Systems;

namespace SDL_Systems {
    class SDL_TimerSystem : public TimerSystem {
    public:
        SDL_TimerSystem() = delete;

        explicit SDL_TimerSystem(int fps);

        void fpsStart() override;

        void fpsCap() override;

        void startTimer() override;

        unsigned int getTime() override;

        void resetTimer() override;

        unsigned int getTimerStep() override;

        unsigned int getTimerAndReset() override;

    private:
        Uint32 fps_time = 0;
        int frame_count = 0;
        Uint32 fps_startTime = 0;
        Uint32 timer_start = 0;
    };
};

#endif //ECS_SDL_TIMERSYSTEM_H
