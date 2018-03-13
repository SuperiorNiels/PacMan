//
// Created by niels on 08/03/18.
//

#include "SDL_TimerSystem.h"

SDL_TimerSystem::SDL_TimerSystem()
{
    SCREEN_FPS = 60;
    SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
    fps_startTime = SDL_GetTicks();
}

SDL_TimerSystem::SDL_TimerSystem(int fps)
{
    SCREEN_FPS = fps;
    SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
    fps_startTime = SDL_GetTicks();
}

void SDL_TimerSystem::start()
{
    time = SDL_GetTicks();
}

void SDL_TimerSystem::cap()
{
    Uint32 new_time = SDL_GetTicks();
    float avgFPS = framecount / (  (new_time-fps_startTime) / 1000.f );
    if( avgFPS > 2000000 )
    {
        avgFPS = 0;
    }
    //std::cout << "[Timing] avg FPS: " << avgFPS << std::endl;
    if( (new_time - time) < SCREEN_TICKS_PER_FRAME )
    {
        //Wait remaining time
        SDL_Delay( SCREEN_TICKS_PER_FRAME - (new_time - time) );
    }
    framecount++;
}