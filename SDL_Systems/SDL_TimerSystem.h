//
// Created by niels on 08/03/18.
//

#ifndef ECS_SDL_TIMERSYSTEM_H
#define ECS_SDL_TIMERSYSTEM_H


#include <SDL_types.h>
#include <SDL_timer.h>
#include "../Systems/TimerSystem.h"

class SDL_TimerSystem : public TimerSystem {
public:
    SDL_TimerSystem();
    explicit SDL_TimerSystem(int fps);
    void start() override;
    void cap() override;
private:
    Uint32 time = 0;
    int framecount = 0;
    Uint32 fps_startTime = 0;
};


#endif //ECS_SDL_TIMERSYSTEM_H
