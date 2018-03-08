//
// Created by niels on 08/03/18.
//

#include "SDL_TimerSystem.h"

void SDL_TimerSystem::update()
{
    Uint32 new_time = SDL_GetTicks();
    std::cout << "[Timing] Average FPS: " << 1000.f / (new_time - time) << std::endl;
    time = new_time;
}