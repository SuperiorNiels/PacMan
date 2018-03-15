//
// Created by niels on 06/03/18.
//

#ifndef ECS_EVENTSYSTEM_H
#define ECS_EVENTSYSTEM_H

#include "../ECS/ECS.h"

enum events_numbers
{
    R_BUTTON
};

class EventSystem : public System
{
public:
    const bool getRunning()
    {
        return running;
    };
    const std::vector<events_numbers> getEvents()
    {
        std::vector<events_numbers> res = events;
        events.clear();
        return res;
    };
protected:
    bool running = true;
    double speed = 0;
    std::vector<events_numbers> events = std::vector<events_numbers>();
};

#endif //ECS_EVENTSYSTEM_H
