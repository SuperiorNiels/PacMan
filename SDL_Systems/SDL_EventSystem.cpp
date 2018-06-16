//
// Created by niels on 06/03/18.
//

#include "SDL_EventSystem.h"

void SDL_EventSystem::update()
{
    // Clear event queue
    events->clear();

    SDL_Event e = {};
    direction dir = STOP; // STOP = 0
    bool update_entities = false;
    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT)
            running = false;

        if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_LEFT:
                    dir = LEFT;
                    update_entities = true;
                    break;
                case SDLK_RIGHT:
                    dir = RIGHT;
                    update_entities = true;
                    break;
                case SDLK_UP:
                    dir = UP;
                    update_entities = true;
                    break;
                case SDLK_DOWN:
                    dir = DOWN;
                    update_entities = true;
                    break;
                case SDLK_SPACE:
                    events->operator[](PAUSE_GAME) = true;
                    break;
                case SDLK_r:
                    events->operator[](RESTART) = true;
                    break;
                case SDLK_t:
                    events->operator[](TEST) = true;
                    break;
                default:
                    break;
            }
        }
    }

    if(update_entities)
    {
        for (auto it : entities)
        {
            auto en = it.second; // get entity
            if(en->hasComponentType(MOVABLE_COMPONENT))
            {
                auto* mc = en->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
                mc->wanted_dir = dir;
                if(!en->hasComponentType(COLLISION_COMPONENT))
                    mc->current_dir = dir;
            }
        }
    }
}