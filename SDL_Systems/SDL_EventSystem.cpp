//
// Created by niels on 06/03/18.
//

#include "SDL_EventSystem.h"


SDL_EventSystem::SDL_EventSystem()
{
    component_types = {PLAYER_INPUT_COMPONENT};
}

void SDL_EventSystem::update()
{
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
                case SDLK_r:
                    events.push_back(R_BUTTON);
                    break;
                case SDLK_p:
                    events.push_back(P_BUTTON);
                    break;
                case SDLK_o:
                    events.push_back(O_BUTTON);
                    break;
                case SDLK_m:
                    events.push_back(M_BUTTON);
                    break;
                default:
                    break;
            }
        }
    }

    if(update_entities)
    {
        for (auto& en : entities)
        {
            if(en->hasComponentType(MOVABLE_COMPONENT))
            {
                auto* mc = en->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
                mc->wanted_dir = dir;
            }
            if(en->hasComponentType(RENDER_COMPONENT))
            {
                auto* rc = en->getComponentByType<RenderComponent>(RENDER_COMPONENT);
                rc->frame_offset = rc->direction_offsets[dir-1];
            }
        }
    }
}