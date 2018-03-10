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
    void update() override;
private:
    Uint32 time = 0;
    std::vector<double> fps = std::vector<double>();
};


#endif //ECS_SDL_TIMERSYSTEM_H
