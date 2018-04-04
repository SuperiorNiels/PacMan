//
// Created by niels on 08/03/18.
//

#include "SDL_TimerSystem.h"

SDL_TimerSystem::SDL_TimerSystem(int fps) : TimerSystem(fps)
{
    fps_startTime = SDL_GetTicks();
}

void SDL_TimerSystem::fpsStart()
{
    fps_time = SDL_GetTicks();
}

void SDL_TimerSystem::fpsCap()
{
    Uint32 new_time = SDL_GetTicks();
    float avgFPS = frame_count / (  (new_time-fps_startTime) / 1000.f );
    if( avgFPS > 2000000 )
    {
        avgFPS = 0;
    }
    //std::cout << "[Timing] avg FPS: " << avgFPS << std::endl;
    if( (new_time - fps_time) < SCREEN_TICKS_PER_FRAME )
    {
        //Wait remaining time
        SDL_Delay( SCREEN_TICKS_PER_FRAME - (new_time - fps_time) );
    }
    frame_count++;
}

void SDL_TimerSystem::startTimer()
{
    timer_start = SDL_GetTicks();
}

unsigned int SDL_TimerSystem::getTimerStep()
{
    return SDL_GetTicks() - fps_time;
}

unsigned int SDL_TimerSystem::getTimerAndReset()
{
    unsigned int res = SDL_GetTicks() - timer_start;
    timer_start = SDL_GetTicks();
    return res;
}