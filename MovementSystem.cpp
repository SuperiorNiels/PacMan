//
// Created by niels on 05/03/18.
//

#include "MovementSystem.h"
#include "PacMan_Constants.h"
#include "SDL_Components.h"

MovementSystem::MovementSystem()
{
    component_types = {0, 1}; // position component, movable component
}

void MovementSystem::update()
{
    for(auto& e : entities)
    {
        auto* p = e->getComponentByType<PositionComponent>(0);
        auto* m = e->getComponentByType<MovableComponent>(1);
        auto* rc = e->getComponentByType<SDL_RenderComponent>(10);
        if(p != nullptr && m != nullptr)
        {
            p->x += m->x_speed;
            p->y += m->y_speed;
            // TODO: use sdl rendercomponent here?
            if(p->x > WINDOW_WIDTH/SCALE_FACTOR)
            {
                p->x = 0;
            }
            if(p->x+rc->clips[rc->current_frame+rc->frame_offset]->w < 0)
            {
                p->x = WINDOW_WIDTH/SCALE_FACTOR;
            }
            if(p->y > WINDOW_HEIGHT/SCALE_FACTOR)
            {
                p->y = 0;
            }
            if(p->y+rc->clips[rc->current_frame+rc->frame_offset]->w < 0)
            {
                p->y = WINDOW_HEIGHT/SCALE_FACTOR;
            }
            //std::cout << "[Movement] \t Moved entity with id: " << e->id << std::endl;
        }
    }
}