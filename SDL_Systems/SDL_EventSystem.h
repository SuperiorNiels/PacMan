//
// Created by niels on 06/03/18.
//

#ifndef ECS_SDL_EVENTSYSTEM_H
#define ECS_SDL_EVENTSYSTEM_H

#include "SDL2/SDL.h"
#include "../Systems/EventSystem.h"
#include "../PacMan_Components.h"
#include "../SDL_Components.h"

class SDL_EventSystem : public EventSystem {
public:
    explicit SDL_EventSystem(std::map<events_numbers, bool> *events) : EventSystem(events) {};
    void update() override;
};


#endif //ECS_SDL_EVENTSYSTEM_H
