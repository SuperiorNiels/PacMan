//
// Created by niels on 06/03/18.
//

#ifndef ECS_EVENTSYSTEM_H
#define ECS_EVENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../PacMan_Components.h"

using namespace ECS;

enum events_numbers
{
    PAUSE_GAME,
    RESTART,
};

class EventSystem : public System
{
public:
    EventSystem() {
        // System settings
        component_types = {PLAYER_INPUT_COMPONENT};
        pausable = false;
    }
    const bool getRunning() { return running; };
    std::map<events_numbers , bool> events;
protected:
    bool running = true;
    //std::vector<events_numbers> events = std::vector<events_numbers>();

};

#endif //ECS_EVENTSYSTEM_H
