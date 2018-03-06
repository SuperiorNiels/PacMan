//
// Created by niels on 06/03/18.
//

#ifndef ECS_EVENTSYSTEM_H
#define ECS_EVENTSYSTEM_H

#include "ECS/ECS.h"

class EventSystem : public System
{
public:
    const bool getRunning() {
        return running;
    };
protected:
    bool running = true;
};

#endif //ECS_EVENTSYSTEM_H
