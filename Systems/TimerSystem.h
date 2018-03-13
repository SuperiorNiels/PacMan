//
// Created by niels on 08/03/18.
//

#ifndef ECS_TIMERSYSTEM_H
#define ECS_TIMERSYSTEM_H

#include "../ECS/ECS.h"

class TimerSystem
{
public:
    virtual void start() = 0;
    virtual void cap() = 0;
protected:
    int SCREEN_FPS = 0;
    int SCREEN_TICKS_PER_FRAME = 0;
};


#endif //ECS_TIMERSYSTEM_H
