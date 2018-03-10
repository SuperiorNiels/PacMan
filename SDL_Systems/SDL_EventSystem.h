//
// Created by niels on 06/03/18.
//

#ifndef ECS_SDL_EVENTSYSTEM_H
#define ECS_SDL_EVENTSYSTEM_H

#include "SDL2/SDL.h"
#include "../Systems/EventSystem.h"

class SDL_EventSystem : public EventSystem {
public:
    SDL_EventSystem();
    void update() override;
};


#endif //ECS_SDL_EVENTSYSTEM_H
