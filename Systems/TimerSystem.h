//
// Created by niels on 08/03/18.
//

#ifndef ECS_TIMERSYSTEM_H
#define ECS_TIMERSYSTEM_H

#include "../ECS/ECS.h"

class TimerSystem
{
public:
    virtual void start() = 0; // fixme: fps en ticks/frame in constructor
    virtual void cap() = 0;
    int getFPS() { return SCREEN_FPS; };
protected:
    int SCREEN_FPS = 0;
    int SCREEN_TICKS_PER_FRAME = 0;
};


#endif //ECS_TIMERSYSTEM_H
