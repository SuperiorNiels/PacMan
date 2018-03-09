//
// Created by niels on 08/03/18.
//

#include "SDL_TimerSystem.h"

void SDL_TimerSystem::update()
{
    Uint32 new_time = SDL_GetTicks();
    if(fps.size() > 120)
    {
        double average = 0;
        for(auto& t : fps)
        {
            average += t;
        }
        std::cout << "[Timing] Average FPS: " << average/120  << std::endl;
        fps.clear();
    }
    else
    {
        fps.push_back(1000.f / (new_time - time));
    }
    time = new_time;
}