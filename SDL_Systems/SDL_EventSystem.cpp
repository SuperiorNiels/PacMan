//
// Created by niels on 06/03/18.
//

#include "SDL_EventSystem.h"
#include "../PacMan_Components.h"
#include "../SDL_Components.h"

SDL_EventSystem::SDL_EventSystem()
{
    component_types = {PLAYER_INPUT_COMPONENT};
}

void SDL_EventSystem::update()
{
    SDL_Event e = {};
    float x_speed = 0;
    float y_speed = 0;
    int direction = 0;
    bool change = false;
    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT)
            running = false;
        if(!entities.empty())
        {
            // If entities not empty, an entity can be controlled so we check for key events
            if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        y_speed = 0;
                        x_speed =  -0.0833;
                        direction = 0;
                        change = true;
                        break;
                    case SDLK_RIGHT:
                        y_speed = 0;
                        x_speed  = 0.0833;
                        direction = 1;
                        change = true;
                        break;
                    case SDLK_UP:
                        x_speed = 0;
                        y_speed = -0.0833;
                        direction = 2;
                        change = true;
                        break;
                    case SDLK_DOWN:
                        x_speed = 0;
                        y_speed = 0.0833;
                        direction = 3;
                        change = true;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    if(change)
    {
        for (auto &en : entities)
        {
            auto *m = en->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
            if (m != nullptr) {
                m->x_speed = x_speed;
                m->y_speed = y_speed;
            }
            auto *rc = en->getComponentByType<SDL_RenderComponent>(RENDER_COMPONENT);
            if (rc != nullptr) {
                rc->frame_offset = rc->direction_offsets[direction];
            }
        }
    }
    //std::cout << "[SDL_Events] SDL_Events updated." << std::endl;
}